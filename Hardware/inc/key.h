/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

/** @defgroup Key_Exported_Types
  * @{
  */

/** 
  * @brief  Key mode enumeration
  */

typedef enum
{ 
  Key_Mode_IPD = 0,
	Key_Mode_IPU = 1
}KeyMode_TypeDef;

/** 
  * @brief  Key state enumeration
  */

typedef enum
{ 
  Key_None_Press = 0,
  Key_Press,
	Key_Short_Press,
  Key_Long_Press,
	Key_Long_Press_Over
}KeyFlag_TypeDef;

/** 
  * @brief  Key struct
  */

typedef struct
{ 
	KeyMode_TypeDef key_mode;
  KeyFlag_TypeDef key_flag;
	uint8_t key_now;
	uint8_t key_last;
	uint8_t key_cnt;
	uint8_t key_lcnt;
	uint32_t key_port;
	uint32_t key_pin;
}Key_TypeDef;

extern Key_TypeDef key1;
extern Key_TypeDef key2;

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */

#define USE_TIM_SCAN_KEY 1

/** @defgroup KEY_PIN */
//#define KEY1_PIN GPIO_PIN_12 // PB12
//#define KEY2_PIN GPIO_Pin_13 // PB13
//#define KEY3_PIN GPIO_Pin_14 // PB14
//#define KEY4_PIN GPIO_Pin_15 // PB15
//#define KEY5_PIN GPIO_Pin_9 // PB9

/**
  * @}
  */

/** @defgroup KEY_Exported_Macros
  * @{
  */ 

/**
  * @}
  */

/** @defgroup KEY_Exported_Functions
  * @{
  */

void Key_Init(Key_TypeDef *keyx, KeyMode_TypeDef mode, uint32_t gpio_periph, uint32_t pin);
#if !USE_TIM_SCAN_KEY
uint8_t Key_Scan(uint8_t mode);
#else
void Key_Scan(Key_TypeDef *keyx);
#endif
void Key_StateScan(Key_TypeDef *keyx);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __KEY_H */

/***** (C) YUNQY 2023 *****END OF FILE*****/
