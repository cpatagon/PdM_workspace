/*
 * API_debounce.c
 *
 *  Created on: 	18-07-2023
 *      @Author: 	Luis Gómez
 *      @Hardware: 	STM32F429ZI
 *      @Objective: Implement a program that toggles the LED2 frequency
 *      			between 100 ms and 500 ms each time the key is pressed. The
 *      			program should use the debounce functions of the API debounce module
 *      			and the non-blocking delays of the API_delay module.
 */
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#include <assert.h>
#include <API_debounce.h>
#include "API_delay.h"

static void buttonPressed(void); // para mas adelante

/*
 * Definition of the states for the state machine
 */

typedef enum {
	BUTTON_UP,       // Button released
	BUTTON_FALLING,  // Button being pressed
	BUTTON_DOWN,     // Button pressed
	BUTTON_RAISING,  // Button being released
} debounceState_t;

typedef enum {
	EDGE_RAISING, EDGE_FALLING, EDGE_INIT,
} Edge_State_t;

// Global and private state variable declaration
static debounceState_t currentState;
static Edge_State_t current_edge_state;

/*
 * Declare a global private variable of type bool_t that
 * is set to true when a falling edge occurs
 * and is set to false when the readKey() function is called.
 */
static bool_t PressButton = true;
static delay_t *delay;

/* Function -------------------------------------------------------------------------------- */

/*
 * @brief   Initializes the FSM with the defined value
 *          at the start of the model.
 *
 * @param   None
 * @retval  None
 */
void debounceFSM_init(delay_t *delayi) {
	/* Initialize Estado */
	assert(&PressButton!=NULL);
	currentState = BUTTON_UP;
	current_edge_state = EDGE_INIT;
	delay = delayi;
	return;
}

/*
 * Function that changes from true to false or from false to true
 * if the button is pressed without bouncing.
 */
bool_t readKey() {
	return PressButton;
}

/**
 * @brief   Funcion que identifica si es flanco de subida o flanco de bajada
 *
 * @param
 * @retval  puntero de caracteres
 */

char* readStatus() {
	assert(&current_edge_state!=NULL);
	char *state_name;
	switch (current_edge_state) {
	case EDGE_RAISING:
		state_name = "EDGE RAISING\n";
		break;
	case EDGE_FALLING:
		state_name = "EDGE FALLING\n";
		break;
	case EDGE_INIT:
		state_name = "\n";
		break;
	default:
		/* Handle unexpected state */
		assert(0);
	}
	return state_name;
}

bool_t isbuttonPressed(void) {
	bool_t state = false;
	if (currentState == BUTTON_DOWN) {
		state = true;
	}
	return state;
}
;

/*
 * @brief   Updates the debounce FSM.
 *          This function reads the inputs, evaluates the transition conditions according to the FSM's current state,
 *          and updates the current state and outputs accordingly.
 *
 * @param   delay: pointer to the delay instance
 * @retval  None
 */
bool_t debounceFSM_update() {
	assert(delay!=NULL);
	assert(&currentState!=NULL);
	bool_t value;
	value = false;

	switch (currentState) {
	/*
	 * In the BUTTON_UP state, it checks whether the button remains unpressed.
	 * Otherwise, that is, if the button is pressed, the state changes to BUTTON_FALLING.
	 */
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER)) {
			currentState = BUTTON_FALLING;
		}
		break;
		/*
		 * In the BUTTON_FALLING state, it checks if the button remains pressed for 40 ms.
		 * If it remains pressed (condition 'yes'), the state changes to BUTTON_DOWN and the
		 * state of LED1 is toggled. If the button does not remain pressed (condition 'no'),
		 * the state changes back to BUTTON_UP, interpreting this event as a bounce.
		 */
	case BUTTON_FALLING:
		if (BSP_PB_GetState(BUTTON_USER) && delayRead(delay)) {
			currentState = BUTTON_DOWN;
			buttonPressed();
			value = true;
			current_edge_state = EDGE_FALLING;
			//PressButton = !(PressButton);
		} else {
			//currentState=BUTTON_DOWN;
			currentState = BUTTON_UP;
		}
		break;
		/*
		 * In the BUTTON_DOWN state, if the button is released, the state changes to BUTTON_RAISING.
		 */
	case BUTTON_DOWN:
		if (!BSP_PB_GetState(BUTTON_USER)) {
			currentState = BUTTON_RAISING;

		}
		break;
		/*
		 * In the BUTTON_RAISING state, it checks if the button remains unpressed for a certain delay.
		 * If it remains unpressed (condition 'yes'), the state changes back to BUTTON_UP and
		 * the buttonReleased function is called. If the button is pressed again (condition 'no'),
		 * the state changes back to BUTTON_DOWN.
		 */
	case BUTTON_RAISING:
		if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)) {
			currentState = BUTTON_UP;
			current_edge_state = EDGE_RAISING;
			//buttonReleased();
		} else {

			currentState = BUTTON_DOWN;
		}
		break;
	default:
		/* Handle unexpected state */
		assert(0);
	}
	return value;
}

/*
 * @brief   Toggles the state of LED2.
 *
 * @param   None
 * @retval  None
 */
static void buttonPressed(void) {
	PressButton = !(PressButton);
	return;
}

/*función que invierte  el estado del LED3 */
/*static void buttonReleased()
 {
 }
 */

