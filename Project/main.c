/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Peripheral Header File */
#include "systick.h"
#include "gpio.h"
#include "timer.h"
#include "adc.h"
#include "usart.h"
/* Hardware Header File */
#include "key.h"
/* Software Header File */

/* Application Header File */
#include "car.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t adc_val = 0, voltage = 0, vol_last = 0, vol_cnt = 0;
extern volatile uint8_t flag_tim5_1ms;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
	systick_config();
	gpio_config();
	timer1_config(199, 9999); // 10ms, 100Hz
	timer2_config(199, 9999); // 10ms, 100Hz
	timer5_config(199, 999); // 1ms, 1KHz
	Key_Init(&key1, Key_Mode_IPU, GPIOE, GPIO_PIN_5); // Key Start
	Key_Init(&key2, Key_Mode_IPU, GPIOB, GPIO_PIN_5); // Key Mode
	adc_config();
	uart6_config(9600U);
	USART_SendString(UART6, "Target RST.");

	while (1)
	{
		if (flag_tim5_1ms) {
			flag_tim5_1ms = 0;
			adc_val = adc_channel_sample(ADC_CHANNEL_15);
			voltage = adc_val * 1.0 / 4095 * 3.3 * 30;
			if (voltage != vol_last) {
				vol_cnt++;
				if (vol_cnt > 1000) {
					vol_cnt = 0;
					vol_last = voltage;
					car.power_voltage = voltage;
				}
			} else {
				vol_cnt = 0;
			}
		}
		
    if (key1.key_flag == Key_Short_Press) {
			key1.key_flag = Key_None_Press;
			LED2_TOGGLE();
			car_run(front, 4999);
		}
		if (key2.key_flag == Key_Short_Press) {
			key2.key_flag = Key_None_Press;
			LED3_TOGGLE();
			car_stop();
		}
	}
}

/***** (C) YUNQY 2023 GD32 *****END OF FILE*****/
