/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

void adc_config(void);
uint16_t adc_channel_sample(uint8_t channel);

#endif /* __ADC_H */
