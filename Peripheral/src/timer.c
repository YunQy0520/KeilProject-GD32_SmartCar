/* Includes ------------------------------------------------------------------*/
#include "timer.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the TIM1.
  * @param  psc, arr.
  * @retval None
  */
void timer1_config(uint16_t psc, uint16_t arr)
{
	timer_parameter_struct timer_initpara;
	timer_oc_parameter_struct timer_ocintpara;
	
	/* gpio configuration */
	rcu_periph_clock_enable(RCU_GPIOA);

	/* Configure PA0 PA1 PA2 PA3 (TIMER1 CH0 CH1 CH2 CH3) as alternate function */
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

	gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	
	/* NVIC configuration */
//	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
  nvic_irq_enable(TIMER1_IRQn, 0, 1);
	
	/* -----------------------------------------------------------------------
    TIMER1 configuration: generate 3 PWM signals with 3 different duty cycles:
    TIMER1CLK = SystemCoreClock / 200 = 1MHz

    TIMER1 channel1 duty cycle = (4000/ 16000)* 100  = 25%
    TIMER1 channel2 duty cycle = (8000/ 16000)* 100  = 50%
    TIMER1 channel3 duty cycle = (12000/ 16000)* 100 = 75%
    ----------------------------------------------------------------------- */
	rcu_periph_clock_enable(RCU_TIMER1);
  rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // CK_TIMERx = 4 * CK_APB1 = 4 * 50 M = 200MHZ
	
	timer_deinit(TIMER1);
	
	/* TIMER1 configuration */
	timer_initpara.prescaler         = psc;
	timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;
	timer_initpara.period            = arr;
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER1,&timer_initpara);
	
	/* CH0, CH1, CH2 and CH3 configuration in PWM mode */
	timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER1, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER1, TIMER_CH_1, &timer_ocintpara);
	timer_channel_output_config(TIMER1, TIMER_CH_2, &timer_ocintpara);
	timer_channel_output_config(TIMER1, TIMER_CH_3, &timer_ocintpara);

	/* CH0 configuration in PWM mode1, duty cycle 25% */
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, 0);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
	
	/* CH1 configuration in PWM mode1, duty cycle 25% */
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 0);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	/* CH2 configuration in PWM mode1, duty cycle 50% */
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, 0);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_2, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

	/* CH3 configuration in PWM mode1, duty cycle 75% */
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_3, 0);
	timer_channel_output_mode_config(TIMER1, TIMER_CH_3, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER1, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER1);
	
	/* TIMER1 update interrupt enable */
	timer_interrupt_disable(TIMER1, TIMER_INT_UP);
	
	/* TIMER1 counter enable */
	timer_enable(TIMER1);
}


/**
  * @brief  Configures the TIM1.
  * @param  psc, arr.
  * @retval None
  */
void timer2_config(uint16_t psc, uint16_t arr)
{
	timer_parameter_struct timer_initpara;
	timer_oc_parameter_struct timer_ocintpara;
	
	/* gpio configuration */
	rcu_periph_clock_enable(RCU_GPIOA);
	rcu_periph_clock_enable(RCU_GPIOB);

	/*Configure PB4 PA7 PB0 PB1 (TIMER2 CH0 CH1 CH2 CH3) as alternate function*/
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
	gpio_af_set(GPIOA, GPIO_AF_2, GPIO_PIN_7);
	
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4);
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4);
	gpio_af_set(GPIOB, GPIO_AF_2, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4);
	
	/* NVIC configuration */
//	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
  nvic_irq_enable(TIMER2_IRQn, 0, 1);
	
	/* -----------------------------------------------------------------------
    TIMER2 configuration: generate 4 PWM signals with 4 different duty cycles:
    TIMER2CLK = SystemCoreClock / 200 = 1MHz

    TIMER2 channel1 duty cycle = (4000/ 16000)* 100  = 25%
    TIMER2 channel2 duty cycle = (8000/ 16000)* 100  = 50%
    TIMER2 channel3 duty cycle = (12000/ 16000)* 100 = 75%
    ----------------------------------------------------------------------- */
	rcu_periph_clock_enable(RCU_TIMER2);
  rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // CK_TIMERx = 4 * CK_APB1 = 4 * 50 M = 200MHZ
	
	timer_deinit(TIMER2);
	
	/* TIMER1 configuration */
	timer_initpara.prescaler         = psc;
	timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;
	timer_initpara.period            = arr;
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER2,&timer_initpara);
	
	/* CH1,CH2 and CH3 configuration in PWM mode */
	timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
	timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
	timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
	timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
	timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
	timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

	timer_channel_output_config(TIMER2, TIMER_CH_0, &timer_ocintpara);
	timer_channel_output_config(TIMER2, TIMER_CH_1, &timer_ocintpara);
	timer_channel_output_config(TIMER2, TIMER_CH_2, &timer_ocintpara);
	timer_channel_output_config(TIMER2, TIMER_CH_3, &timer_ocintpara);

	/* CH1 configuration in PWM mode1, duty cycle 25% */
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_0, 0);
	timer_channel_output_mode_config(TIMER2, TIMER_CH_0, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER2, TIMER_CH_0, TIMER_OC_SHADOW_DISABLE);
	
	/* CH1 configuration in PWM mode1, duty cycle 25% */
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 0);
	timer_channel_output_mode_config(TIMER2, TIMER_CH_1, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER2, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);

	/* CH2 configuration in PWM mode1, duty cycle 50% */
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, 0);
	timer_channel_output_mode_config(TIMER2, TIMER_CH_2, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER2, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

	/* CH3 configuration in PWM mode1, duty cycle 75% */
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, 0);
	timer_channel_output_mode_config(TIMER2, TIMER_CH_3, TIMER_OC_MODE_PWM0);
	timer_channel_output_shadow_config(TIMER2, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);

	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER2);
	
	/* TIMER2 update interrupt enable */
	timer_interrupt_disable(TIMER2, TIMER_INT_UP);
	
	/* TIMER2 counter enable */
	timer_enable(TIMER2);
}

/**
  * @brief  Configures the TIM5.
  * @param  psc, arr.
  * @retval None
  */
void timer5_config(uint16_t psc, uint16_t arr)
{
	timer_parameter_struct timer_initpara;
	
	/* system clocks configuration */
	rcu_periph_clock_enable(RCU_TIMER5);
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4); // CK_TIMERx = 4 * CK_APB1 = 4 * 50 M = 200MHZ
	
	/* NVIC configuration */
	nvic_irq_enable(TIMER5_DAC_IRQn, 3, 2);
	
	timer_deinit(TIMER5);
	
	/* TIMER5 configuration */
	timer_initpara.prescaler         = psc; // Prescale 0 ~ 65535  psc_clk = CK_TIMER / psc
	timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
	timer_initpara.counterdirection  = TIMER_COUNTER_UP;
	timer_initpara.period            = arr;
	timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
	timer_initpara.repetitioncounter = 0;
	timer_init(TIMER5, &timer_initpara);
	
	/* auto-reload preload enable */
	timer_auto_reload_shadow_enable(TIMER5);
	
	/* TIMER5 update interrupt enable */
	timer_interrupt_enable(TIMER5, TIMER_INT_UP);
	
	/* TIMER5 counter enable */
	timer_enable(TIMER5);
}

void pwm_led4_breath(void)
{
//	static uint8_t direct = 0; //??
//	static uint16_t value = 0; //???

//	if (direct == 0) //????
//	{
//		value += 300; //?????
//		if (value > 10000)
//			direct = 1; //????
//	}
//	else //????
//	{
//			value -= 300; //?????
//			if (value <= 0)
//					direct = 0;
//	}
//	timer_channel_output_pulse_value_config(PWM_LED4_TIMER, PWM_LED4_TIMER_CHANNEL, value); // ????????????
}

/***** (C) YUNQY 2023 GD32 *****END OF FILE*****/
