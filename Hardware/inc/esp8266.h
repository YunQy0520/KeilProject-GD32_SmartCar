/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ESP8266_H
#define __ESP8266_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup ESP8266
  * @{
  */ 

/** @defgroup EPS8266_Exported_Types
  * @{
  */

/* The mode of ESP8266 */
typedef enum
{
  STA,
  AP,
  STA_AP
}ESP8266_ModeTypeDef;

/* Network Transport Layer Protocol */
typedef enum
{
  enumTCP,
  enumUDP,
}NetProtocol_TypeDef;

/**
  * @}
  */

/** @defgroup ESP8266_Exported_Constants
  * @{
  */

#define REV_OK		0	// Receive complete flag
#define REV_WAIT	1	// Receive not complete flag

#define ESP8266_RST_PORT GPIOA
#define ESP8266_RST_PIN GPIO_Pin_15

#define ESP8266_RST_PIN_SET() GPIO_SetBits(ESP8266_RST_PORT, ESP8266_RST_PIN)
#define ESP8266_RST_PIN_RESET() GPIO_ResetBits(ESP8266_RST_PORT, ESP8266_RST_PIN)

#define MQTT_BUFFER_SIZE_BYTE 512

#define ESP8266_WIFI_SSID	"YunQy-Y7000"
#define ESP8266_WIFI_PWD	"yunqy0520"

#define ESP8266_MQTT_CLIENTID	"ESP8266-01"
#define ESP8266_MQTT_USERNAME	"YunQy"
#define ESP8266_MQTT_USERPWD	"yunqy0520"
#define ESP8266_MQTT_IP				"broker.emqx.io"
#define ESP8266_MQTT_PORT			1883
#define ESP8266_MQTT_Topic		"YunQy_IoT/ESP8266-01"

/**
  * @}
  */

/** @defgroup ESP8266_Exported_Functions
  * @{
  */

void ESP8266_Rst(void);
void ESP8266_Clear(void);
void ESP8266_SendData(char *data);
uint8_t ESP8266_AP_Status(void);
_Bool ESP8266_AP_Join(char *pSSID, char *pPassword);
uint8_t ESP8266_LinkStatus(void);
uint8_t *ESP8266_GetIPD(unsigned short timeOut);
void ESP8266_Init(void);
_Bool ESP8266_MQTT_UserConfig(char *pClientID, char *pUserName, char *pPassword);
_Bool ESP8266_MQTT_Connect(char *pIP, uint8_t port);
_Bool ESP8266_MQTT_Pub(char *pTopic, char *pData, uint8_t qos);
_Bool ESP8266_MQTT_PubRaw(char *pTopic, uint16_t length, uint8_t qos);
_Bool ESP8266_MQTT_Sub(char *pTopic, uint8_t qos);
_Bool ESP8266_MQTT_Unsub(char *pTopic);
_Bool ESP8266_MQTT_Clean(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ESP8266_H */
