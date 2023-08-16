/**
 * @file API_delay.c
 * @brief Implementation of functions for managing delays on STM32F4xx.
 * @date 06-07-2023
 * @author lgomez
 */

#include "stm32f4xx_hal.h"          ///< HAL (Hardware Abstraction Layer) for STM32F4.
#include "stm32f4xx_nucleo_144.h"   ///< BSP (Board Support Package) for Nucleo-144.
#include <assert.h>
#include "API_delay.h"

/**
 * @brief Initialize the delay object with the specified duration.
 *
 * This function initializes a delay object, setting its duration and
 * marking the `running` flag as false. It doesn't start the delay count.
 *
 * @param delay Pointer to the delay object.
 * @param duration Duration of the delay in ticks.
 */
void delayInit(delay_t *delay, tick_t duration) {
	assert(delay != NULL);
	assert(duration >= 0);
	delay->duration = duration;
	delay->running = false;
}

/**
 * @brief Reads and updates the state of the delay object.
 *
 * If the delay is not running, it takes a timestamp and starts it.
 * If it is running, it checks if the delay has reached its duration and, if so,
 * resets the object and returns true.
 *
 * @param delay Pointer to the delay object.
 * @return true if the delay has reached its duration, false otherwise.
 */
bool_t delayRead(delay_t *delay) {
	static bool_t retValue; ///< Internal static variable to hold the return value.
	retValue = false;
	assert(delay != NULL);
	assert(delay->duration >= 0);

	if (!delay->running) {
		delay->startTime = HAL_GetTick();
		delay->running = true;
	} else {
		if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
			delay->running = false;
			retValue = true;
		}
	}
	return retValue;
}

/**
 * @brief Sets a new duration for the delay object.
 *
 * @param delay Pointer to the delay object.
 * @param duration New duration in ticks.
 */
void delayWrite(delay_t *delay, tick_t duration) {
	assert(delay != NULL);
	assert(duration >= 0);
	delay->duration = duration;
}
