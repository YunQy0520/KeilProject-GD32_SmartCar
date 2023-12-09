/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures the USART0.
  * @param  baud.
  * @retval None
  */
void usart0_config(uint32_t baud)
{
	/* enable GPIO clock */
	rcu_periph_clock_enable(RCU_GPIOA);

	/* enable UART clock */
	rcu_periph_clock_enable(RCU_USART0);

	/* configure the UART6 TX and RX pins */
	gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9 | GPIO_PIN_10);

	/* configure UART6 TX and Rx as alternate function push-pull */
	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9 | GPIO_PIN_10);
	gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9 | GPIO_PIN_10);

	/* NVIC configuration */
	nvic_irq_enable(USART0_IRQn, 2, 1);
	
	/* USART configure */
	usart_deinit(USART0);
	usart_baudrate_set(USART0, baud);
	usart_parity_config(USART0, USART_PM_NONE);
	usart_word_length_set(USART0, USART_WL_8BIT);
	usart_stop_bit_set(USART0, USART_STB_1BIT);
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	usart_enable(USART0);
}

/**
  * @brief  Configures the UART6.
  * @param  baud.
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
	usart_parity_config(UART6, USART_PM_NONE);
	usart_word_length_set(UART6, USART_WL_8BIT);
	usart_stop_bit_set(UART6, USART_STB_1BIT);
	usart_receive_config(UART6, USART_RECEIVE_ENABLE);
	usart_transmit_config(UART6, USART_TRANSMIT_ENABLE);
	usart_interrupt_enable(UART6, USART_INT_RBNE);
	usart_enable(UART6);
}

void USART_SendByte(uint32_t USARTx, uint8_t byte)
{
	usart_data_transmit(USARTx, byte);
	while (RESET == usart_flag_get(USARTx, USART_FLAG_TBE));
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
		USART_SendByte(USARTx, array[i]);
	}
}

/**
  * @brief  Use USARTx to send string.
  * @param  USARTx, string
  * @retval None
  */
void USART_SendString(uint32_t USARTx, char *str)
{
	while (str && *str)
		USART_SendByte(USARTx, *str++);
}

/***** (C) YUNQY 2023 GD32 *****END OF FILE*****/
