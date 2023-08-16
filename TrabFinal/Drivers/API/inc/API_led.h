/*
 * API_led.h
 *
 *  Created on: Aug 6, 2023
 *      Author: lgomez
 *
 */

/*
 * Library responsible for manipulating the 8x8 led matrix
 * with the IC MAX7219ENG. Through an SPI protocol
 * with different functions:
 *
 * - init_led()   = for initialization
 * - clear_led()  = all leds turned off
 * - lit_led()    = all leds turned on
 * - update_led() = displays an image
 * - row_led()    =
 * - ghost_led()  =
 *
 * All communication is carried out via the SPI protocol
 * implemented in the API_spi.h library.
 *
 * Also included is a set of predefined images ready to
 * be used in update_led()
 * */

#ifndef API_INC_API_LED_H_
#define API_INC_API_LED_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* @brief   Parameter for controlling the LED matrix. */

/* FSM Display States */
static uint8_t smileyFace[] = { 0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C }; // Smiley face for GOOD state
static uint8_t A[] = { 0x00, 0x7c, 0x12, 0x12, 0x12, 0x12, 0x7c, 0x00 }; // Letter A 
static uint8_t B[] = { 0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x34, 0x00 }; // Letter B
static uint8_t C[] = { 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x24, 0x00 }; // Letter C

/* @brief LED Bar Score Representations */
static uint8_t zero[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // No rows lit
static uint8_t one[] = { 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0 }; // Two rows lit
static uint8_t two[] = { 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0 }; // Four rows lit
static uint8_t three[] = { 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC }; // Six rows lit
static uint8_t four[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // All rows lit
static uint8_t heart[] = { 0x0C, 0x1E, 0x3E, 0x7C, 0x3E, 0x1E, 0x0C, 0x00 }; // Heart shape pattern
static uint8_t *levels_led[] = { zero, one, two, three, four, heart }; // LED level bar 

/* @brief   Function responsible for initializing the LED matrix.
 * @param   void
 * @retval  void
 * */
void init_led(void);

/* @brief   Function responsible for clearing the LED screen,
 *          setting all the matrix values to 0.
 * @param   void
 * @retval  void
 * */
void clear_led(void);

/* @brief   Function responsible for lighting up all the LEDs
 *          in the matrix.
 * @param   void
 * @retval  void
 * */
void lit_led(void);

/* @brief   Function responsible for lighting up the LEDs according
 *          to the given design in list form.
 * @param   paint_list[] List where each row represents
 *          a value of a row written in hexadecimal form of a
 *          binary representation of the row where 0 is LED off
 *          and 1 is LED on.
 * @retval  void
 * */
void update_led(uint8_t paint_list[]);

/**
 * @brief Updates the LED status based on a row.
 *
 * This function takes a list of values and updates the LED status according
 * to the provided list.
 *
 * @param paint_list List with the LED values.
 */
void row_led(uint8_t fila);

/**
 * @brief Generates a ghost animation.
 *
 * This function creates a ghost function on the LED screen.
 *
 * @param void
 */
void ghost_led(void);

#endif /* API_INC_API_LED_H_ */
