/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HCSR04_H
#define __HCSR04_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

/** @addtogroup HCSR04
  * @{
  */ 

/** @defgroup HCSR04_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup HCSR04_Exported_Constants
  * @{
  */

#define HCSR04_TRIG_PIN	GPIO_PIN_12 // PB12
#define HCSR04_ECHO_PIN	GPIO_PIN_10 // PB10

#define HCSR04_TRIG(bit_val) gpio_bit_write(GPIOB, HCSR04_TRIG_PIN, (bit_status)bit_val)
#define HCSR04_ECHO_VAL()	gpio_input_bit_get(GPIOB, HCSR04_ECHO_PIN)

/**
  * @}
  */

/** @defgroup HCSR04_Exported_Functions
  * @{
  */

void HCSR04_Init(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __HCSR04_H */
