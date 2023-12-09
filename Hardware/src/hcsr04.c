/* Includes ------------------------------------------------------------------*/
#include "hcsr04.h"
#include "systick.h"
#include "gpio.h"
#include "timer.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define USE_TIMER_CAP
#define USE_EXTI

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint8_t HCSR04_Get = 0;
volatile int32_t HCSR04_Distance = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize the HCSR04.
  * @param  None
  * @retval None
  */
void HCSR04_Init(void)
{
	/* system clocks configuration */
	rcu_periph_clock_enable(RCU_GPIOB);

	gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HCSR04_TRIG_PIN);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HCSR04_TRIG_PIN);
	gpio_bit_write(GPIOB, HCSR04_TRIG_PIN, RESET);
	
#ifndef USE_TIMER_CAP
	gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, HCSR04_ECHO_PIN);
	#ifdef USE_EXTI
	timer6_config(19, 9); // 1us, 1MHz
	
	rcu_periph_clock_enable(RCU_SYSCFG);
	
	nvic_irq_enable(EXTI10_15_IRQn, 1U, 1U);
	
	/* connect EXTI line to ECHO pin */
	syscfg_exti_line_config(EXTI_SOURCE_GPIOB, EXTI_SOURCE_PIN10);
	exti_init(EXTI_10, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
	exti_interrupt_flag_clear(EXTI_10);
	
	#endif
#else
	/*configure PB10 (TIMER1 CH2) as alternate function*/
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_10);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

	gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_10);
#endif
}

/**
  * @brief  Reset the ESP8266.
  * @param  None
  * @retval None
  */
int32_t HCSR04_Get_Distance(void)
{
	uint32_t t=0;//Echo高电平时间
	int32_t d=0;
	
	HCSR04_TRIG(1);
	delay_1us(20);
	HCSR04_TRIG(0);
	
	t=0;
	while (HCSR04_ECHO_VAL() == 0) {
		delay_1us(1);
		t++;
		
		if(t >= 1000000)
			return -1;//设备响应超时处理
	}
	
	t=0;
	while (HCSR04_ECHO_VAL())
	{
		
		delay_1us(9); 
		t++;
		
		if(t >= 10000)//超出测量范围处理
			return -2;	
	}
	
	d =  t*3/2;
	return  d;
}

#ifdef USE_EXTI

uint16_t tim6_cnt = 0;

/*!
    \brief      this function handles TIMER6 interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER6_IRQHandler(void)
{
	if (timer_interrupt_flag_get(TIMER6, TIMER_INT_FLAG_UP) == SET) {
		/* clear TIMER interrupt flag */
		timer_interrupt_flag_clear(TIMER6, TIMER_INT_FLAG_UP);
		tim6_cnt++;
	}
}

__IO uint16_t ReadValue1 = 0, ReadValue2 = 0;
__IO uint16_t CaptureNumber = 0;
__IO uint32_t Capture = 0;

/*!
    \brief      this function handles external lines 10 to 15 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void EXTI10_15_IRQHandler(void)
{
	if (RESET != exti_interrupt_flag_get(EXTI_10)) {
//		if (CaptureNumber == 0) {
//			/* Get CNT value1 of TIMER1 */
//			ReadValue1 = TIMER_CNT(TIMER1);
//			CaptureNumber = 1;
//		} else if (CaptureNumber == 1) {
//			/* Get CNT value2 of TIMER1 */
//			ReadValue2 = TIMER_CNT(TIMER1);
//			
//			/* Capture computation */
//			if (ReadValue2 > ReadValue1) {
//				Capture = (ReadValue2 - ReadValue1);
//			} else {
//				Capture = ((0xFFFF - ReadValue1) + ReadValue2);
//				CaptureNumber = 0;
//			}
//		}
		if (CaptureNumber == 0) {
			/* Enable TIMER6 */
			timer_enable(TIMER6);
			CaptureNumber = 1;
		} else if (CaptureNumber == 1) {
			/* Disable TIMER6 */
			timer_disable(TIMER6);
			
			if (tim6_cnt >= 38000) {
				HCSR04_Distance = -1;
			} else {
				Capture = tim6_cnt;
				HCSR04_Distance = Capture * 340 / 10000 / 2;
			}
			HCSR04_Get = 1;
			TIMER_CNT(TIMER6) = 0;
			tim6_cnt = 0;
			CaptureNumber = 0;
		}
		exti_interrupt_flag_clear(EXTI_10);
	}
}
#endif

/***** (C) YUNQY 2023 *****END OF FILE*****/
