#include <stdint.h>  /* esta para incluir los tipos uint32_t */
#include <stdbool.h> /* esta para incluir los tipos bool (boolianos) */

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#include "API_delay.h" /* <- Aquí está la inclusión del archivo que define delay_t */


typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t; // Qué biblioteca se debe incluir para que esto compile?

 /* La función readKey debe leer una variable interna
  * del módulo y devolver true o false si la tecla fue
  * presionada.  Si devuelve true, debe resetear
  * (poner en false) el estado de la variable.*/

bool_t readKey();

void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update( delay_t*);	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
/*static void buttonPressed();			// debe invertir el estado del LED1
static void buttonReleased();// debe invertir el estado del LED3
*/
