/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

/** @defgroup USART_Exported_Functions */
void usart0_config(uint32_t baud);
void uart6_config(uint32_t baud);
void USART_SendArray(uint32_t USARTx, uint16_t array_length, uint8_t *array);
void USART_SendString(uint32_t USARTx, char *str);
	
#endif /* __USART_H */
