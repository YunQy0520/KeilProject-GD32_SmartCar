/* Includes ------------------------------------------------------------------*/
#include "car.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  The car stop.
  * @param  None
  * @retval None
  */
void car_stop(void)
{
	/* Right front wheel */
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_3, 0);
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, 0);

	/* Right back wheel */
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, 0);
	timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 0);
	
	/* Left front wheel */
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 0);
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_0, 0);
	
	/* Left back wheel */
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, 0);
	timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, 0);
}

/**
  * @brief  The car go front.
  * @param  None
  * @retval None
  */
void car_run(CarDirection_Typedef direction, uint16_t speed)
{
	switch (direction) {
		case front:
			/* Right front wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_3, speed);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, 0);
		
			/* Right back wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, speed);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 0);
			
			/* Left front wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, speed);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_0, 0);
			
			/* Left back wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, speed);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, 0);
			break;
		case back:
			/* Right front wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_3, 0);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, speed);
		
			/* Right back wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, 0);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, speed);
			
			/* Left front wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 0);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_0, speed);
			
			/* Left back wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, 0);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, speed);
			break;
		case left:
			/* Right front wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_3, speed);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, 0);
		
			/* Right back wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, speed);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, 0);
			
			/* Left front wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 0);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_0, speed);
			
			/* Left back wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, 0);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, speed);
			break;
		case right:
			/* Right front wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_3, 0);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_2, speed);
		
			/* Right back wheel */
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_0, 0);
			timer_channel_output_pulse_value_config(TIMER1, TIMER_CH_1, speed);
		
			/* Left front wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, speed);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_0, 0);
			
			/* Left back wheel */
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_3, speed);
			timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_2, 0);
			break;
	}
}

/***** (C) YUNQY 2023 GD32 *****END OF FILE*****/
