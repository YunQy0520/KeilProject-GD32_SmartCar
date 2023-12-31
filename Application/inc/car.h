/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAR_H
#define __CAR_H

/* Includes ------------------------------------------------------------------*/
#include "gd32f4xx.h"

typedef enum
{
	front = 0,
	back,
	left,
	right
}CarDirection_Typedef;

typedef struct
{
	uint8_t mode;
	CarDirection_Typedef cardir;
	uint16_t power_voltage;
}Car_TypeDef;

extern Car_TypeDef car;

void car_stop(void);
void car_run(CarDirection_Typedef direction, uint16_t speed);

#endif /* __CAR_H */
