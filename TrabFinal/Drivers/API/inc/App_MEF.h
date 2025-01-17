/**
 * @file 	:	App_MEF.h
 * @date 	: 	Aug 6, 2023
 * @author 	: 	lgomez
 * @brief 	: 	Definitions and function prototypes for the game's finite state machine (FSM).
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

#ifndef API_INC_APP_MEF_H_
#define API_INC_APP_MEF_H_

#include "API_delay.h"       /**< Includes the file that defines delay_t. */
#include "API_debounce.h"    /**< Includes the library to manage button debouncing. */

/**
 * @brief Enumeration of the possible states of the FSM of the game.
 */
typedef enum {
	SET_ini, /**< Initial state of the FSM and show score. */
	FIRST, /**< First state after the start. */
	SECOND, /**< Second state. */
	THIRD, /**< Third state. */
	GOOD, /**< 'Good' state. */
	BAD /**< 'Bad' state. */
} State_MEF_t;

/**
 * @brief Initializes the finite state machine.
 */
void init_MEF(void);

/**
 * @brief Updates the current state of the FSM based on inputs and conditions.
 *
 * @param delay Pointer to the delay structure.
 * @return State_MEF_t: The updated state of the FSM.
 */
State_MEF_t update_MEF(delay_t *delay);

#endif /* API_INC_APP_MEF_H_ */

