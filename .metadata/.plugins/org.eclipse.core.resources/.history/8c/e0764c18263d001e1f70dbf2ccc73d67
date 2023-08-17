/**
 * @file 	:	App_MEF.c
 * @date 	: 	Aug 6, 2023
 * @author 	: 	lgomez
 * @brief 	: 	"Implementation of the finite state machine."
 *
 * 				This FSM governs the game's operation through distinct logical sequences. Initially,
 * 				the game showcases the starting score in the SET_ini state. Players then witness a
 * 				rotating sequence of characters (A, B, C) on the screen, while awaiting a button press.
 *
 * 				A button press during the C state leads to a victory, incrementing the player's score
 * 				by 1. Notably, both score tracking and game speed adjustments are handled in the main.c
 * 				for enhanced configurability. However, if the button is pressed during either the A or B
 * 				states, the player loses, forfeiting all accumulated points and restarting the game.
 * 				After five consecutive wins, players are rewarded with a heart display on the LED screen.
 *
 * @attention : All functionalities related to game speeds, scores, and display rendering
 * 				are controlled within main.c.
 *
 */

#include "stm32f4xx_hal.h"  		/**< Inclusión de la biblioteca HAL. */
#include "stm32f4xx_nucleo_144.h" 	/**< Inclusión de la biblioteca BSP. */

#include <assert.h>
#include "App_MEF.h"
#include "API_debounce.h"

#define TIME_DEBOUNCE 40 // Debounce time for the button

/** Variable that holds the current state of the FSM. */
static State_MEF_t estadoMEF;

static delay_t DelayDebounce; // Debounce time for the button

/**
 * @brief Function to initialize the FSM. Sets the initial state.
 */
void init_MEF(void) {
	estadoMEF = SET_ini; /**< Set the initial state. */
	// Initialize the Finite State Machine (FSM) for debounce.
	delayInit(&DelayDebounce, TIME_DEBOUNCE);
	debounceFSM_init(&DelayDebounce);
	return;
}

/**
 * @brief 	Updates the FSM based on the current state and inputs such as
 * 			pressing the button and/or the passing of a certain amount of time.
 *
 * 			This function evaluates the current state of the FSM and determines the next
 * 			state based on input conditions.
 *
 * @param 	delay Pointer to the delay_t data type that defines the delay structure,
 * 			i.e., the game's transition speed.
 * @return 	State_MEF_t represents the updated state of the FSM.
 */
State_MEF_t update_MEF(delay_t *delay) {
	// Ensure the pointer to the current state is not null.
	assert(&estadoMEF!=NULL);

	// Switch case for the current state of the FSM.
	switch (estadoMEF) {
	case SET_ini:
		// At this moment, the score is being displayed on the LED display.
		// If the delay time has passed, transition to the FIRST state.
		if (delayRead(delay)) {
			estadoMEF = FIRST;
		}
		break;

	case FIRST:
		// At this moment, the letter A is being displayed on the LED display.
		// If the button debounce is handled and the delay time has passed, transition to the SECOND state.
		// If the USER button is pressed and the delay time hasn't passed, transition to the BAD state.
		if (!debounceFSM_update() && delayRead(delay)) {
			estadoMEF = SECOND;
		} else if (BSP_PB_GetState(BUTTON_USER) && !delayRead(delay)) {
			estadoMEF = BAD;
		}
		break;

	case SECOND:
		// At this moment, the letter B is being displayed on the LED display.
		// Similar logic as the FIRST state but transitions to the THIRD state.
		if (!debounceFSM_update() && delayRead(delay)) {
			estadoMEF = THIRD;
		} else if (BSP_PB_GetState(BUTTON_USER) && !delayRead(delay)) {
			estadoMEF = BAD;
		}
		break;

	case THIRD:
		// At this moment, the letter C is being displayed on the LED display.
		// If the button debounce is handled and the delay time has passed, loop back to the FIRST state.
		// If the USER button is pressed and the delay time hasn't passed, transition to the GOOD state.
		if (!debounceFSM_update() && delayRead(delay)) {
			estadoMEF = FIRST;
		} else if (BSP_PB_GetState(BUTTON_USER) && !delayRead(delay)) {
			estadoMEF = GOOD;
		}
		break;

	case GOOD:
		// The player wins the round and the score is incremented.
		// At this moment, a smiling face is displayed on the LED screen, and the score counter increases.
		// The gameplay speed also increases.
		// If the USER button isn't pressed and the delay time has passed, reset to the SET_ini state.
		if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)) {
			estadoMEF = SET_ini;
		}
		break;

	case BAD:
		// The player loses the round.
		// At this moment, a ghost is displayed on the LED screen, and the score is reurnig to our.
		// The gameplay speed also increases.
		// If the USER button isn't pressed and the delay time has passed, reset to the SET_ini state.
		if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)) {
			estadoMEF = SET_ini;
		}
		break;

	default:
		// In case of reaching an undefined state, force an interruption.
		assert(0);
	}

	// Return the updated FSM state.
	return (estadoMEF);
}

