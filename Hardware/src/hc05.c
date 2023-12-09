/* Includes ------------------------------------------------------------------*/
#include "hc05.h"
#include "systick.h"
#include "usart.h"
/* C Headed File */
#include <string.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DEBUG_USART USART0

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//unsigned char esp8266_buf[512];
//unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

///**
//  * @brief  Clear cache of ESP8266.
//  * @param  None
//  * @retval None
//  */
//void ESP8266_Clear(void)
//{
//	memset(esp8266_buf, 0, sizeof(esp8266_buf));
//	esp8266_cnt = 0;
//}

///**
//  * @brief  Reset the ESP8266.
//  * @param  None
//  * @retval None
//  */
//void ESP8266_Rst(void)
//{
//	ESP8266_Clear();
//	ESP8266_RST_PIN_RESET();
//	delay_ms(500); 
//	ESP8266_RST_PIN_SET();
//}

///**
//  * @brief  Waiting for receive complete.
//  * @param  None
//  * @retval REV_OK - commplete | REV_WAIT - time out and not complete
//  */
//_Bool ESP8266_WaitRecive(void)
//{
//	/* Not at the state of receive data, break the function. */
//	if (esp8266_cnt == 0)
//		return REV_WAIT;
//	
//	/* The last value is same as this time, receiving completed. */
//	if (esp8266_cnt == esp8266_cntPre) {
//		esp8266_cnt = 0; // Clear the cnt.
//		return REV_OK;
//	}
//	
//	esp8266_cntPre = esp8266_cnt;
//	return REV_WAIT;
//}

///**
//  * @brief  Send the cmd.
//  * @param  cmd
//  * @param  res Return commands that need to be checked
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_SendCmd(char *cmd, char *res)
//{
//	uint8_t timeout = 200;

//	USART_SendString(ESP8266_DRIVER_USART, (char *)cmd);
//	
//	while (timeout--)
//	{
//		/* If received data. */
//		if (ESP8266_WaitRecive() == REV_OK) {
//			/* If keywords are retrieved. */
//			if (strstr((const char *)esp8266_buf, res) != NULL) {
////				ESP8266_Clear(); // Clear the cache.
//				return 0;
//			}
//		}
//		delay_ms(10);
//	}
//	return 1;
//}

///**
//  * @brief  Send the data.
//  * @param  data
//  * @param  length
//  * @retval 0 - success | 1 - fail
//  */
//void ESP8266_SendData(char *data)
//{
//	ESP8266_Clear();
//	/* When received '>', the data can be sent */
//	if (!ESP8266_SendCmd("AT+CIPSEND=%d\r\n", ">")) {
//		/* Send device connection request data. */
//		USART_SendString(ESP8266_DRIVER_USART, data);
//	}
//}

///**
//  * @brief  Get the AP status.
//  * @param  None
//  * @retval 0 - connected | 1 - get fail | 2 - disconnected
//  */
//uint8_t ESP8266_AP_Status(void)
//{
//	if (!ESP8266_SendCmd("AT+CWJAP?\r\n", "OK")) {
//		if (strstr((const char *)esp8266_buf, ESP8266_WIFI_SSID)) {
//			ESP8266_Clear();
//			return 0; // AP connected
//		} else {
//			ESP8266_Clear();
//			return 2; // No AP
//		}
//	}
//	ESP8266_Clear();
//	return 1; // Get status fail
//}

///**
//  * @brief  Join the AP (Link to WLAN).
//  * @param  pSSID - The ID of AP.
//  * @param  pPassWord - The password of AP.
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_AP_Join(char *pSSID, char *pPassword)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", pSSID, pPassword);
//  return ESP8266_SendCmd(cmd, "GOT IP");
//}

///**
//  * @brief  Get the link status.
//  * @param  None
//  * @retval 1 - Get status fail | 2 - Got IP
//						3 - Build connection | 4 - Lose connection
//  */
//uint8_t ESP8266_LinkStatus(void)
//{
//	if (!ESP8266_SendCmd("AT+CIPSTATUS\r\n", "OK")) {
//		/* If keywords are retrieved. */
//		if (strstr((const char *)esp8266_buf, "STATUS:2\r\n")) {
//			ESP8266_Clear(); // Clear the cache.
//			return 2;
//		} else if (strstr((const char *)esp8266_buf, "STATUS:3\r\n")) {
//			ESP8266_Clear(); // Clear the cache.
//			return 3;
//		} else if (strstr((const char *)esp8266_buf, "STATUS:4\r\n")) {
//			ESP8266_Clear(); // Clear the cache.
//			return 4;
//		}
//	}
//	ESP8266_Clear();
//	return 1;
//}

///**
//  * @brief  Obtain the data returned by the platform.
//  * @param  Waiting time (Multiply by 10ms)
//  * @retval Raw data returned by the platform. 
//						Different network devices return different formats.
//						Such as the format of ESP8266 is: "+IPD,x:yyy", 
//						the 'x' is the length of data, "yyy" is the content of data.
//  */
//uint8_t *ESP8266_GetIPD(unsigned short timeout)
//{

//	char *ptrIPD = NULL;
//	
//	do {
//		/* If reception is complete */
//		if (ESP8266_WaitRecive() == REV_OK) {
//			ptrIPD = strstr((char *)esp8266_buf, "IPD,"); // Search for "IPD" head.
//			/* If not found, it may be an IPD delay that requires waiting for a while, 
//				 but will not exceed the set value. */
//			if (ptrIPD == NULL) {
//				USART_SendString(DEBUG_USART, "\"IPD\" not found\r\n");
//			} else {
//				ptrIPD = strchr(ptrIPD, ':'); // Find the ':'
//				if (ptrIPD != NULL) {
//					ptrIPD++;
//					return (unsigned char *)(ptrIPD);
//				} else
//					return NULL;
//			}
//		}
//		
//		delay_ms(5); // Delay to wait
//		timeout--;
//	} while (timeout > 0);
//	
//	/* The timeout has not been found yet, returning a null pointer */
//	return NULL;
//}

/**
  * @brief  Initialize the ESP8266.
  * @param  None
  * @retval None
  */
void HC05_Init(void)
{
	/* System clocks configuration */
	rcu_periph_clock_enable(RCU_GPIOF);

	/* GPIO configuration */
	gpio_mode_set(HC05_STATE_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE, HC05_STATE_PIN);
	gpio_mode_set(HC05_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HC05_EN_PIN);
	gpio_output_options_set(HC05_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HC05_EN_PIN);
	gpio_bit_write(HC05_EN_PORT, HC05_EN_PIN, RESET);
	
	/* USART configuration */
	uart6_config(38400U);
	
//	delay_1ms(1000);
//	delay_1ms(1000);
//	delay_1ms(1000);
//	delay_1ms(1000);
//	delay_1ms(1000);
	
	/* Enable the HC-05 to AT mode */
//	HC05_EN(1);
	
	delay_1ms(1000);
//	USART_SendString(DEBUG_USART, "0. AT+RESET\r\n");
//	USART_SendString(UART6, "AT+RESET\r\n");
	delay_1ms(1000);
	delay_1ms(1000);
	delay_1ms(1000);
	USART_SendString(DEBUG_USART, "1. AT\r\n");
	USART_SendString(UART6, "AT\r\n");
	delay_1ms(500);
	USART_SendString(DEBUG_USART, "2. AT+NAME=YunQy-HC05\r\n");
	USART_SendString(UART6, "AT+NAME=HC05\r\n");
	delay_1ms(500);
	USART_SendString(DEBUG_USART, "3. AT+NAME?\r\n");
	USART_SendString(UART6, "AT+NAME?\r\n");
	delay_1ms(500);
	USART_SendString(DEBUG_USART, "4. AT+PSWD=0520\r\n");
	USART_SendString(UART6, "AT+PSWD=0520\r\n");
	delay_1ms(500);
	USART_SendString(DEBUG_USART, "5. AT+ADDR?\r\n");
	USART_SendString(UART6, "AT+ADDR?\r\n");
	delay_1ms(500);
	USART_SendString(DEBUG_USART, "6. AT+RESET\r\n");
	USART_SendString(UART6, "AT+RESET\r\n");
	delay_1ms(1000);
	
//	HC05_EN(0);
	
	USART_SendString(DEBUG_USART, "HC-05 Init OK\r\n");
}

///**
//  * @brief  Configures the user attribute of MQTT.
//						AT+MQTTUSERCFG=<LinkID>,<scheme>,<"client_id">,<"username">,<"password">,<cert_key_ID>,<CA_ID>,<"path">
//  * @param  pClientID - The ID of client.
//  * @param  pUserName
//  * @param  pPassWord
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_MQTT_UserConfig(char *pClientID, char *pUserName, char *pPassword)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"", pClientID, pUserName, pPassword);
//	return ESP8266_SendCmd(cmd, "OK");
//}

///**
//  * @brief  The status of MQTT.
//						AT+MQTTCONN?
//  * @param 	None
//  * @retval 0 - success | 1 - fail
//  */
//uint8_t ESP8266_MQTT_Status(void)
//{
//	if (!ESP8266_SendCmd("AT+MQTTCONN?\r\n", "OK")) {
//		if (strstr((const char *)esp8266_buf, ESP8266_MQTT_IP)) {
//			ESP8266_Clear();
//			return 0; // MQTT connected
//		} else if (strstr((const char *)esp8266_buf, "No AP")) {
//			ESP8266_Clear();
//			return 2; // No AP
//		}
//	}
//	ESP8266_Clear();
//	return 1; // Get status fail
//}

///**
//  * @brief  Connect to MQTT.
//						AT+MQTTCONN=<LinkID>,<"host">,<port>,<reconnect>
//						The link ID only support 0 now.
//  * @param  pIP - The IP of MQTT
//  * @param  port - Normal is 1883
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_MQTT_Connect(char *pIP, uint8_t port)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+MQTTCONN=0,\"%s\",%d,0", pIP, port);
//	return ESP8266_SendCmd(cmd, "OK");
//}

///**
//  * @brief  Publish MQTT string messages trough topic. 
//						To publish binary messages, use the MQTTPUBRAW.
//						AT+MQTTPUB=<LinkID>,<"topic">,<"data">,<qos>,<retain>
//						The link ID only support 0 now.
//  * @param  pTopic - The name of topic. The max length is 128 byte.
//  * @param  pData - The data to be published.
//  * @param  qos - 0 | 1 | 2. Default is 0.
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_MQTT_Pub(char *pTopic, char *pData, uint8_t qos)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+MQTTPUB=0,\"%s\",\"%s\",%d", pTopic, pData, qos);
//	return ESP8266_SendCmd(cmd, "OK");
//}

///**
//  * @brief  Publish MQTT raw messages trough topic. 
//						AT+MQTTPUBRAW=<LinkID>,<"topic">,<length>,<qos>,<retain>
//						The link ID only support 0 now.
//  * @param  pTopic - The name of topic. The max length is 128 byte.
//  * @param  length - The length of message. The ESP8266 is 512 (message + topic).
//  * @param  qos - 0 | 1 | 2. Default is 0.
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_MQTT_PubRaw(char *pTopic, uint16_t length, uint8_t qos)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+MQTTPUBRAW=0,\"%s\",%d,%d", pTopic, length, qos);
//	return ESP8266_SendCmd(cmd, "OK");
//}

///**
//  * @brief  Subscribe to topic
//						AT+MQTTSUB=<LinkID>,<"topic">,<qos>
//						The link ID only support 0 now.
//  * @param  pTopic - The name of topic
//  * @param  qos - 0 | 1 | 2
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_MQTT_Sub(char *pTopic, uint8_t qos)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+MQTTSUB=0,\"%s\",%d", pTopic, qos);
//	return ESP8266_SendCmd(cmd, "OK");
//}

///**
//  * @brief  Unsubscribe from topic
//						AT+MQTTUNSUB=<LinkID>,<"topic">
//						The link ID only support 0 now.
//  * @param  pTopic - The name of topic
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_MQTT_Unsub(char *pTopic)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+MQTTUNSUB=0,\"%s\"", pTopic);
//	return ESP8266_SendCmd(cmd, "OK");
//}

///**
//  * @brief  Disconnect the MQTT connection and release resources.
//						AT+MQTTCLEAN=<LinkID>
//						The link ID only support 0 now.
//  * @param  None
//  * @retval 0 - success | 1 - fail
//  */
//_Bool ESP8266_MQTT_Clean(void)
//{
//	char cmd[120];
//	sprintf(cmd, "AT+MQTTCLEAN=0");
//	return ESP8266_SendCmd(cmd, "OK");
//}

///**
//  * @brief  This function handles USART2 global interrupt request.
//  * @param  None
//  * @retval None
//  */
//void USART2_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
//		if (esp8266_cnt >= sizeof(esp8266_buf)) esp8266_cnt = 0;
//		/* Read one byte from the receive data register */
//		esp8266_buf[esp8266_cnt++] = USART_ReceiveData(USART2);
//	}
//}

/**
  * @}
  */ 

/***** (C) YUNQY 2023 *****END OF FILE*****/
