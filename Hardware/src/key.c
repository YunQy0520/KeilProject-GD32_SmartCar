/* Includes ------------------------------------------------------------------*/
#include "key.h"

/** @addtogroup Key
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Key_TypeDef key1;
Key_TypeDef key2;

/* Private function prototypes -----------------------------------------------*/
static void RCC_Configuration(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
static void RCC_Configuration(void)
{
  /* PCLK2 = HCLK/2 */
//  RCC_PCLK2Config(RCC_HCLK_Div2);

  /* Enable peripheral clocks */
  rcu_periph_clock_enable(RCU_GPIOB);
	rcu_periph_clock_enable(RCU_GPIOE);
}

/**
  * @brief  Initialize the keys.
  * @param  None
  * @retval None
  */
void Key_Init(Key_TypeDef *keyx, KeyMode_TypeDef mode, uint32_t gpio_periph, uint32_t pin)
{
	/* System clocks configuration ---------------------------------------------*/
  RCC_Configuration();
	
  /* GPIO configuration ------------------------------------------------------*/
	if (mode == Key_Mode_IPU)
		gpio_mode_set(gpio_periph, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, pin);
	else if (mode == Key_Mode_IPD)
		gpio_mode_set(gpio_periph, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, pin);
	
	keyx->key_mode = mode;
	keyx->key_port = gpio_periph;
	keyx->key_pin = pin;
	keyx->key_flag = Key_None_Press;
	keyx->key_now = 0;
	if (mode == Key_Mode_IPU)
		keyx->key_last = 1;
	else
		keyx->key_last = 0;
	keyx->key_cnt = 0;
	keyx->key_lcnt = 0;
}

/**
  * @brief  This function is to scan the keys.
  * @param  mode: 0, no | 1, support for continuous pressing
  * @retval 0, No key pressed | 1, KEY1 | 2, KEY2
	* @note   Response priority: KEY1 > KEY2
  */
#if !USE_TIM_SCAN_KEY
uint8_t Key_Scan(uint8_t mode)
{
	static uint8_t key_up = 1;
	if (mode) key_up = 1;
	if (key_up && (KEY1_STATE == 1 || KEY2_STATE == 0)) {
		delay_ms(10);
		key_up = 0;
		if (KEY1_STATE == 1) return 1;
		else if (KEY2_STATE == 0) return 2;
	}
	else if (KEY1_STATE == 0 && KEY2_STATE == 0) key_up = 1;
	return 0;
}
#else
/**
  * @brief  This function is to scan the keys.
  * @param  mode: 0, no | 1, support for continuous pressing
  * @retval 0, No key pressed | 1, KEY1 | 2, KEY2
	* @note   Response priority: KEY1 > KEY2
  */
void Key_Scan(Key_TypeDef *keyx)
{
	keyx->key_now = gpio_input_bit_get(keyx->key_port, keyx->key_pin);
	
	/* Edge detection */
	if (keyx->key_now != keyx->key_last) {
		keyx->key_cnt++;
		/* Shake down to determine whether the button is pressed or released */
		if (keyx->key_cnt > 12) {
			keyx->key_cnt = 0; // clear the cnt
			keyx->key_last = keyx->key_now; // refresh the temp of key state
			if (keyx->key_mode == Key_Mode_IPU) {
				if (!keyx->key_now) {
					keyx->key_flag = Key_Press;
				} else if (keyx->key_flag != Key_Long_Press_Over) {
					keyx->key_flag = Key_Short_Press;
				}
			} else {
				if (keyx->key_now) {
					keyx->key_flag = Key_Press;
				} else if (keyx->key_flag != Key_Long_Press_Over) {
					keyx->key_flag = Key_Short_Press;
				}
			}
		}
	} else {
		keyx->key_cnt = 0; // clear the cnt
	}
	
	/* Long press detection */
	if (keyx->key_flag == Key_Press) {
		keyx->key_lcnt++;
		if (keyx->key_lcnt >= 160) {
			keyx->key_lcnt = 0; // clear the cnt
			keyx->key_flag = Key_Long_Press;
		}
	} else {
		keyx->key_lcnt = 0; // clear the cnt
	}
}
#endif

/**
  * @brief  This function is to scan the keys.
  * @param  mode: 0, no | 1, support for continuous pressing
  * @retval 0, No key pressed | 1, KEY1 | 2, KEY2
	* @note   Response priority: KEY1 > KEY2
  */
void Key_StateScan(Key_TypeDef *keyx)
{
	keyx->key_now = gpio_input_bit_get(keyx->key_port, keyx->key_pin);
	
	/* Edge detection */
	if (keyx->key_now != keyx->key_last) {
		keyx->key_cnt++;
		/* Shake down to determine whether the button is pressed or released */
		if (keyx->key_cnt > 3) {
			keyx->key_cnt = 0; // clear the cnt
			keyx->key_last = keyx->key_now; // refresh the temp of key state
			if (keyx->key_mode == Key_Mode_IPU) {
				if (!keyx->key_now) {
					keyx->key_flag = Key_Press;
				} else {
					keyx->key_flag = Key_Short_Press;
				}
			} else {
				if (keyx->key_now) {
					keyx->key_flag = Key_Press;
				} else {
					keyx->key_flag = Key_Short_Press;
				}
			}
		}
	} else {
		keyx->key_cnt = 0; // clear the cnt
	}
}

/**
  * @}
  */ 

/***** (C) YUNQY 2023 *****END OF FILE*****/
