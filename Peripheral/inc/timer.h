/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TIMER_H
#define _TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

/** @defgroup Timer_Exported_Functions */
void timer1_config(uint16_t psc, uint16_t arr);
void timer2_config(uint16_t psc, uint16_t arr);
void timer5_config(uint16_t psc, uint16_t arr);

#endif
