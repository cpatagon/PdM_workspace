/**
 * @file API_delay.h
 * @brief Interface for handling time delays on STM32F4xx.
 * @date 07-08-2023
 * @author lgomez
 *
 * This header file defines an interface for managing time delays.
 * Delays can be initialized, read, and adjusted as required.
 * The implementation uses the specific HAL (Hardware Abstraction Layer) 
 * and BSP (Board Support Package) for the STM32F4xx Nucleo-144 board.
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_

#include <stdint.h>  // For standard type definitions, e.g., uint32_t.
#include <stdbool.h> // For the boolean type (bool).
#include "stm32f4xx_hal.h"          ///< HAL (Hardware Abstraction Layer) for STM32F4.
#include "stm32f4xx_nucleo_144.h"   ///< BSP (Board Support Package) for Nucleo-144.

/// Defines the 'tick_t' type for managing time ticks.
typedef uint32_t tick_t;

/// Defines the 'bool_t' type for handling boolean values.
typedef bool bool_t;

/// @brief Structure to manage a time delay.
typedef struct {
	tick_t startTime; ///< Timestamp marking the start of the delay.
	tick_t duration;  ///< Duration of the delay in ticks.
	bool_t running;   ///< Indicates whether the delay is active or not.
} delay_t;

/**
 * @brief Initialize a delay object.
 *
 * @param delay Pointer to the delay object to initialize.
 * @param duration Duration of the delay in ticks.
 */
void delayInit(delay_t *delay, tick_t duration);

/**
 * @brief Reads and updates the status of the delay object.
 *
 * @param delay Pointer to the delay object to read.
 * @return true if the delay time has elapsed, false otherwise.
 */
bool_t delayRead(delay_t *delay);

/**
 * @brief Sets a new duration for the delay.
 *
 * @param delay Pointer to the delay object to modify.
 * @param duration New duration of the delay in ticks.
 */
void delayWrite(delay_t *delay, tick_t duration);

#endif /* API_INC_API_DELAY_H_ */

