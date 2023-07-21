/*
 * API_debounce.c
 *
 *  Created on: 18-07-2023
 *      @Author: Luis Gómez
 *      @Hardware: STM32F429ZI
 *      @Objetivo: Implementar un programa que cambie la
 *      frecuencia de toggleo del LED2 entre 100 ms y 500
 *      ms cada vez que se presione la tecla.  El programa
 *      debe usar las funciones anti-rebote del módulo API
 *      debounce y los retardos no bloqueantes del módulo
 *      API_delay.
 *
 */
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#include <assert.h>
#include "API_debounce.h"

/* funciones propias
 *
 * Función Inicializar MEF con el valor definido
 * en el inicio del modelo
 * */

bool_t PressButton=true;


bool_t readKey(){
 return PressButton;
}

void debounceFSM_init(debounceState_t * EstadoActual, debounceState_t Valor){
	/* Initialize Estado */
	*EstadoActual=Valor;
}

/*
 * This function reads inputs, manages the transition between states,
 * and updates the outputs accordingly.
 */
void debounceFSM_update(debounceState_t * currentState, delay_t* delay){
	switch (*currentState){
	/*
	 * In the BUTTON_UP state, it checks whether the button remains unpressed.
	 * Otherwise, that is, if the button is pressed, the state changes to BUTTON_FALLING.
	 */
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER)){
	    	*currentState=BUTTON_FALLING;
		}
		break;
		/*
		 * In the BUTTON_FALLING state, it checks if the button remains pressed for 40 ms.
		 * If it remains pressed (condition 'yes'), the state changes to BUTTON_DOWN and the
		 * state of LED1 is toggled. If the button does not remain pressed (condition 'no'),
		 * the state changes back to BUTTON_UP, interpreting this event as a bounce.
		 */
	case BUTTON_FALLING:
		if (BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
	    	*currentState=BUTTON_DOWN;
	    	//buttonPressed();
	    	PressButton = !(PressButton);
		}
		else {
			*currentState=BUTTON_UP;
		}
		break;
	/*
	 * In the BUTTON_DOWN state, if the button is released, the state changes to BUTTON_RAISING.
	 */
	case BUTTON_DOWN:
		if (!BSP_PB_GetState(BUTTON_USER)){
	    	*currentState=BUTTON_RAISING;
		}
		break;
	/*
	 * In the BUTTON_RAISING state, it checks if the button remains unpressed for a certain delay.
	 * If it remains unpressed (condition 'yes'), the state changes back to BUTTON_UP and
	 * the buttonReleased function is called. If the button is pressed again (condition 'no'),
	 * the state changes back to BUTTON_DOWN.
	 */
	case BUTTON_RAISING:
		if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
	    	*currentState=BUTTON_UP;
	    	//buttonReleased();
		}
		else {
			*currentState=BUTTON_DOWN;
		}
		break;
	default:
			/* Handle unexpected state */
		assert(0);
	}
}

/* función que invierte  el estado del LED1 */
static void buttonPressed(){
	if (readKey()){
	BSP_LED_Toggle(LED2);
	}
	else {BSP_LED_Toggle(LED1);}
}

/* función que invierte  el estado del LED3 */
static void buttonReleased()
{
	//BSP_LED_Toggle(LED3);
}

