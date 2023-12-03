/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the TIM1.
  * @param  psc, arr.
  * @retval None
  */
void uart6_config(uint32_t baud)
{
	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOF);

	/* enable UART clock */
	rcu_periph_clock_enable(RCU_UART6);

	/* configure the UART6 TX and RX pins */
	gpio_af_set(GPIOF, GPIO_AF_8, GPIO_PIN_6 | GPIO_PIN_7);

	/* configure UART6 TX and Rx as alternate function push-pull */
	gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_6 | GPIO_PIN_7);
	gpio_output_options_set(GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);

	/* NVIC configuration */
	nvic_irq_enable(UART6_IRQn, 2, 2);
	
	/* USART configure */
	usart_deinit(UART6);
	usart_baudrate_set(UART6, baud);
	usart_receive_config(UART6, USART_RECEIVE_ENABLE);
	usart_transmit_config(UART6, USART_TRANSMIT_ENABLE);
	usart_interrupt_enable(UART6, USART_INT_RBNE);
	usart_enable(UART6);
}

/**
  * @brief  Use USARTx to send array.
  * @param  USARTx, array_length, array
  * @retval None
  */
void USART_SendArray(uint32_t USARTx, uint16_t array_length, uint8_t *array)
{
	uint16_t i;
	for (i = 0; i < array_length; i++) {
		usart_data_transmit(USARTx, array[i]);
	}
}

/**
  * @brief  Use USARTx to send string.
  * @param  USARTx, string
  * @retval None
  */
void USART_SendString(uint32_t USARTx, char *string)
{
	uint16_t i;
	for (i = 0; string[i] != '\0'; i++) {
		usart_data_transmit(USARTx, string[i]);
	}
}

/***** (C) YUNQY 2023 GD32 *****END OF FILE*****/
