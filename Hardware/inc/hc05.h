/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HC05_H
#define __HC05_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

/** @addtogroup HC05
  * @{
  */ 

/** @defgroup HC05_Exported_Types
  * @{
  */

/* The mode of HC05 */
//typedef enum
//{
//  STA,
//  AP,
//  STA_AP
//}HC05_ModeTypeDef;

/**
  * @}
  */

/** @defgroup HC05_Exported_Constants
  * @{
  */

#define HC05_STATE_PORT	GPIOF
#define HC05_STATE_PIN	GPIO_PIN_9 // PF9

#define HC05_EN_PORT	GPIOF
#define HC05_EN_PIN		GPIO_PIN_10 // PF10

#define HC05_EN(bit_val)	gpio_bit_write(HC05_EN_PORT, HC05_EN_PIN, (bit_status)bit_val)

/**
  * @}
  */

/** @defgroup HC05_Exported_Functions
  * @{
  */

//void HC05_Rst(void);
//void HC05_Clear(void);
//void HC05_SendData(char *data);
//uint8_t HC05_AP_Status(void);
//_Bool HC05_AP_Join(char *pSSID, char *pPassword);
//uint8_t HC05_LinkStatus(void);
//uint8_t *HC05_GetIPD(unsigned short timeOut);
void HC05_Init(void);
//_Bool HC05_MQTT_UserConfig(char *pClientID, char *pUserName, char *pPassword);
//_Bool HC05_MQTT_Connect(char *pIP, uint8_t port);
//_Bool HC05_MQTT_Pub(char *pTopic, char *pData, uint8_t qos);
//_Bool HC05_MQTT_PubRaw(char *pTopic, uint16_t length, uint8_t qos);
//_Bool HC05_MQTT_Sub(char *pTopic, uint8_t qos);
//_Bool HC05_MQTT_Unsub(char *pTopic);
//_Bool HC05_MQTT_Clean(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __HC05_H */
