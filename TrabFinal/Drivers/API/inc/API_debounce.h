/**
 * @file API_debounce.h
 * @brief Interfaz de funciones para manejo y eliminación de rebotes en pulsadores.
 * @date Aug 9, 2023
 * @author lgomez
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdint.h>  /**< For standard uint32_t types */
#include <stdbool.h> /**< For standard boolean types */

#include "stm32f4xx_hal.h"          /**< HAL library inclusion */
#include "stm32f4xx_nucleo_144.h"   /**< BSP library inclusion */

#include "API_delay.h" /**< Inclusion of the file defining delay_t */

typedef uint32_t tick_t; /**< Define tick_t as a type alias for uint32_t. Required library: stdint.h */
typedef bool bool_t; /**< Define bool_t as a type alias for bool. Required library: stdbool.h */

/**
 * @brief Reads an internal variable and returns whether the key was pressed.
 * If the function returns true, it resets the state of the variable (sets it to false).
 *
 * @return bool_t: the state of the key (true if the key was pressed, false otherwise)
 */
bool_t readKey();

/**
 * @brief Initializes the debounce FSM, setting the initial state.
 *
 * @param delayi Pointer to the delay instance.
 */
void debounceFSM_init(delay_t *delayi);

/**
 * @brief Updates the debounce FSM.
 * This function reads the inputs, evaluates the transition conditions according to the FSM's current state,
 * and updates the current state and outputs accordingly.
 *
 * @return bool_t: the updated state of the FSM (true or false).
 */
bool_t debounceFSM_update(void);

/**
 * @brief Identifies if the edge is rising or falling.
 *
 * @return Pointer to a character string indicating the status.
 */
char* readStatus();

/**
 * @brief Checks if the button is pressed.
 *
 * @return bool_t: true if the button is pressed, false otherwise.
 */
bool_t isbuttonPressed(void);

/**
 * @brief Internal function to handle button press events.
 *
 * @note This function is static and should only be accessed within its source file.
 */

#endif /* API_INC_API_DEBOUNCE_H_ */
