#include <stdint.h>  /* esta para incluir los tipos uint32_t */
#include <stdbool.h> /* esta para incluir los tipos bool (boolianos) */

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#include "API_delay.h" /* <- Aquí está la inclusión del archivo que define delay_t */


typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t; // Qué biblioteca se debe incluir para que esto compile?

typedef enum{
	BUTTON_UP, // Botón suelto
	BUTTON_FALLING, // Apretando botón
	BUTTON_DOWN,  // Boton precionado
	BUTTON_RAISING, // soltando botón
} debounceState_t;

// Declaración de la variable de estado global y privada
static debounceState_t debounceState;

bool_t readKey();

void debounceFSM_init(debounceState_t*, debounceState_t);		// debe cargar el estado inicial
void debounceFSM_update(debounceState_t*, delay_t*);	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
static void buttonPressed();			// debe invertir el estado del LED1
static void buttonReleased();// debe invertir el estado del LED3