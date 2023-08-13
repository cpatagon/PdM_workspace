/*
 * API_delay2.h
 *
 *  Created on: 07-08-2023
 *      Author: lgomez
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdint.h>  /* esta para incluir los tipos uint32_t */
#include <stdbool.h> /* esta para incluir los tipos bool (boolianos) */

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

typedef uint32_t tick_t; // biblioteca se debe incluir para que esto compile
typedef bool bool_t; // biblioteca se debe incluir para que esto compile
typedef struct{
		tick_t startTime;
		tick_t duration;
		bool_t running;
	} delay_t;

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

#endif /* API_INC_API_DELAY2_H_ */
