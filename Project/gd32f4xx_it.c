/*!
    \file    gd32f4xx_it.c
    \brief   interrupt service routines

    \version 2016-08-15, V1.0.0, firmware for GD32F4xx
    \version 2018-12-12, V2.0.0, firmware for GD32F4xx
    \version 2020-09-30, V2.1.0, firmware for GD32F4xx
    \version 2022-03-09, V3.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32f4xx_it.h"
#include "main.h"
#include "systick.h"
#include "gpio.h"
#include "key.h"
#include "car.h"
#include "communication.h"

/*!
    \brief    this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief    this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while(1) {
    }
}

/*!
    \brief    this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief    this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief    this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief    this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    delay_decrement();
}

/*!
    \brief      this function handles TIMER1 interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER1_IRQHandler(void)
{
	if (timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP) == SET) {
		/* clear TIMER interrupt flag */
		timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);
		
	}
}

/*!
    \brief      this function handles TIMER2 interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER2_IRQHandler(void)
{
	if (SET == timer_interrupt_flag_get(TIMER2, TIMER_INT_CH0)) {
		/* clear channel 0 interrupt bit */
		timer_interrupt_flag_clear(TIMER2,TIMER_INT_CH0);
		/* read channel 0 capture value */
//		ic1value = timer_channel_capture_value_register_read(TIMER2,TIMER_CH_0)+1;

//		if (0 != ic1value){
//			/* read channel 1 capture value */
//			ic2value = timer_channel_capture_value_register_read(TIMER2,TIMER_CH_1)+1;

//			/* calculate the duty cycle value */
//			dutycycle = (ic2value * 100) / ic1value;
//			/* calculate the frequency value */
//			frequency = 1000000 / ic1value;

//		} else {
//			dutycycle = 0;
//			frequency = 0;
//		}
	}
}

volatile uint8_t flag_tim5_1ms = 0, flag_tim5_100ms = 0;
uint16_t tim5_100ms_cnt = 0, tim5_1s_cnt = 0;

/*!
    \brief      this function handles TIMER5 interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void TIMER5_DAC_IRQHandler(void)
{
	if (timer_interrupt_flag_get(TIMER5, TIMER_INT_FLAG_UP) == SET) {
		/* clear TIMER interrupt flag */
		timer_interrupt_flag_clear(TIMER5, TIMER_INT_FLAG_UP);
		
		flag_tim5_1ms = 1;
		
		Key_Scan(&key1);
		Key_Scan(&key2);
		
		if (tim5_100ms_cnt < 100 - 1) {
			tim5_100ms_cnt++;
		} else {
			/* Clear the cnt */
			tim5_100ms_cnt = 0;
			/* Set the flag */
			flag_tim5_100ms = 1;
		}
		
		if (tim5_1s_cnt < 1000 - 1) {
			tim5_1s_cnt++;
		} else {
			/* Clear the cnt */
			tim5_1s_cnt = 0;
			LED1_TOGGLE();
			if (car.power_voltage < 66) {
				LEDS_TOGGLE();
			} else {
				LEDS(0);
			}
		}
	}
}

//uint16_t tim6_cnt = 0;

/*!
    \brief      this function handles TIMER6 interrupt request.
    \param[in]  none
    \param[out] none
    \retval     none
*/
//void TIMER6_IRQHandler(void)
//{
//	if (timer_interrupt_flag_get(TIMER6, TIMER_INT_FLAG_UP) == SET) {
//		/* clear TIMER interrupt flag */
//		timer_interrupt_flag_clear(TIMER6, TIMER_INT_FLAG_UP);
//		tim6_cnt++;
//	}
//}

uint8_t usart0_rx_byte = 0;

/*!
    \brief      this function handles USART0 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_IRQHandler(void)
{
	if (usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE) != RESET) {
		/* clear RBNE IDLE flag */
		usart0_rx_byte = usart_data_receive(USART0);
	}
}

/*!
    \brief      this function handles external lines 10 to 15 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
//void EXTI10_15_IRQHandler(void)
//{
//	if (RESET != exti_interrupt_flag_get(EXTI_10)) {

//		exti_interrupt_flag_clear(EXTI_10);
//	}
//}

uint8_t uart6_rx_byte = 0;

/*!
    \brief      this function handles UART6 interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UART6_IRQHandler(void)
{
	if (usart_interrupt_flag_get(UART6, USART_INT_FLAG_RBNE) != RESET) {
		/* clear RBNE IDLE flag */
		uart6_rx_byte = usart_data_receive(UART6);
		usart_data_transmit(USART0, uart6_rx_byte);
//		Framing(uart6_rx_byte);
	}
}
