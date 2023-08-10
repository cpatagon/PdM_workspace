#include <stdint.h>  /* esta para incluir los tipos uint32_t */
#include <stdbool.h> /* esta para incluir los tipos bool (boolianos) */

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t; // Qué biblioteca se debe incluir para que esto compile?
typedef struct{
		tick_t startTime;
		tick_t duration;
		bool_t running;
	} delaydebounce_t;

void delayInitD( delaydebounce_t* delay, tick_t duration );
bool_t delayReadD( delaydebounce_t * delay );
void delayWriteD( delaydebounce_t * delay, tick_t duration );



