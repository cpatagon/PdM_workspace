/**
 * @file App_MEF.h
 * @brief Definitions and function prototypes for the application's finite state machine (FSM).
 * @date Aug 6, 2023
 * @author lgomez
 */

#ifndef API_INC_APP_MEF_H_
#define API_INC_APP_MEF_H_

#include "API_delay.h"       /**< Includes the file that defines delay_t. */
#include "API_debounce.h"    /**< Includes the library to manage button debouncing. */

/**
 * @brief Enumeration of the possible states of the FSM.
 */
typedef enum {
	SET_ini, /**< Initial state of the FSM. */
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

/**
 * @brief Reads and returns the current state of the FSM.
 *
 * @note This function is currently incomplete and needs to be implemented.
 *
 * @return char*: A string representation of the current state.
 */
//char *Lee_estado();
#endif /* API_INC_APP_MEF_H_ */

