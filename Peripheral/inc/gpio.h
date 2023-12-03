/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

#define LED1_PIN    		GPIO_PIN_3 // PE3
#define LED1(bit_value)	gpio_bit_write(GPIOE, LED1_PIN, (bit_status)bit_value)
#define LED1_TOGGLE()		gpio_bit_toggle(GPIOE, LED1_PIN);

#define LED2_PIN				GPIO_PIN_7 // PD7
#define LED2(bit_value)	gpio_bit_write(GPIOD, LED2_PIN, (bit_status)bit_value)
#define LED2_TOGGLE()		gpio_bit_toggle(GPIOD, LED2_PIN);

#define LED3_PIN    		GPIO_PIN_3 // PG3
#define LED3(bit_value)	gpio_bit_write(GPIOG, LED3_PIN, (bit_status)bit_value)
#define LED3_TOGGLE()		gpio_bit_toggle(GPIOG, LED3_PIN);

#define LED4_PIN    		GPIO_PIN_5 // PA5
#define LED4(bit_value)	gpio_bit_write(GPIOA, LED4_PIN, (bit_status)bit_value)
#define LED4_TOGGLE()		gpio_bit_toggle(GPIOA, LED4_PIN);

#define LEDS_PIN	    	GPIO_PIN_2 // PE2
#define LEDS(bit_value)	gpio_bit_write(GPIOE, LEDS_PIN, (bit_status)bit_value)
#define LEDS_TOGGLE()		gpio_bit_toggle(GPIOE, LEDS_PIN);

#define LEDM_PIN	    	GPIO_PIN_3 // PB3
#define LEDM(bit_value)	gpio_bit_write(GPIOB, LEDM_PIN, (bit_status)bit_value)
#define LEDM_TOGGLE()		gpio_bit_toggle(GPIOB, LEDM_PIN);

#define LEDL_PIN    		GPIO_PIN_12 // PA12
#define LEDL(bit_value)	gpio_bit_write(GPIOA, LEDL_PIN, (bit_status)!bit_value)
#define LEDL_TOGGLE()		gpio_bit_toggle(GPIOA, LEDL_PIN);

#define LEDR_PIN    		GPIO_PIN_7 // PG7
#define LEDR(bit_value)	gpio_bit_write(GPIOG, LEDR_PIN, (bit_status)!bit_value)
#define LEDR_TOGGLE()		gpio_bit_toggle(GPIOG, LEDR_PIN);

#define BEEP_PIN				GPIO_PIN_8 // PF8
#define BEEP(bit_val)		gpio_bit_write(GPIOF, BEEP_PIN, (bit_status)!bit_val)
#define BEEP_TOGGLE()		gpio_bit_toggle(GPIOF, BEEP_PIN);

/** @defgroup GPIO_Exported_Functions */
void gpio_config(void);

#endif /* __GPIO_H */

/***** (C) YUNQY 2023 GD32 *****END OF FILE*****/
