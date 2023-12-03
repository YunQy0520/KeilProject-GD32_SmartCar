/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Peripheral Header File */
#include "systick.h"
#include "gpio.h"
#include "timer.h"
/* Hardware Header File */
#include "key.h"
/* Software Header File */
#include "car.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
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

	while (1)
	{
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
