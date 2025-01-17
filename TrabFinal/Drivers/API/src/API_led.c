/**
 * @file API_led.c
 * @brief Implementation of functions for LED management using SPI.
 * @date Aug 6, 2023
 * @author lgomez
 */

#include <stdint.h>
#include "API_spi.h"
#include "API_delay.h"
#include <assert.h>

#define TIMEGHOST 200 // delay time between ghost animation
#define NULLGHOST 0 // Null ghost error
#define NULLROW 0 // Null row error 
#define ROW_MATRIX 8 // number of rows in a LED matrix display
#define INI_ROW_MATRIX 0 // Count start row matrix led

/**
 *  configuration parameters for the MAX7219 integrated circuit
 *   address */
#define ADDRESS_DECODING 		0x09     // No decoding.
#define ADDRESS_SCAN_LIMIT 		0x0b     // Scan limit = 8 LEDs.
#define ADDRESS_POWER 			0x0c     // Power down = 0, normal mode = 1.
#define ADDRESS_TEST_DISPLAY 	0x0f     // No test display.
#define ADDRESS_BRIGHTNESS 		0x0a     // Brightness intensity.
/*  value */
#define VALUE_DECODING 			0x00	// No decoding.
#define VALUE_SCAN_LIMIT 		0x07	// Scan limit = 8 LEDs.
#define VALUE_POWER 			0x01	// Power down = 0, normal mode = 1.
#define VALUE_TEST_DISPLAY 		0x00	// No test display.
#define VALUE_BRIGHTNESS 		0x05	// Brightness intensity.

/* defines the addresses of the rows in the 8x8 LED matrix */

#define ROW_1	0x01
#define ROW_2	0x02
#define ROW_3	0x03
#define ROW_4	0x04
#define ROW_5	0x05
#define ROW_6	0x06
#define ROW_7	0x07
#define ROW_8	0x08

#define LED_OFF  0x00 // LED ROWS OFF
#define LED_ON   0xFF // LED ROWS ON

uint8_t led_address[] =
		{ ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8 };
uint8_t clear[] = { LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF, LED_OFF,
LED_OFF, LED_OFF };
uint8_t LitMatrix[] = { LED_ON, LED_ON, LED_ON, LED_ON, LED_ON, LED_ON, LED_ON,
LED_ON };

static uint8_t ghost1[] = { 0xFC, 0xFE, 0x6B, 0xEF, 0xEF, 0x6B, 0xfE, 0xFC };
static uint8_t ghost2[] = { 0xFC, 0xFE, 0x6F, 0xEB, 0xEF, 0x6B, 0xfE, 0xFC };
static uint8_t ghost3[] = { 0xFC, 0xFE, 0x7F, 0xEB, 0xEF, 0x6B, 0xfE, 0xFC };
static uint8_t ghost4[] = { 0xFC, 0xFE, 0x7F, 0xFB, 0xEF, 0x6B, 0xfE, 0xFC };
static uint8_t ghost5[] = { 0xFC, 0xFE, 0x7B, 0xFF, 0xEF, 0x6B, 0xfE, 0xFC };

delay_t delayGhost; // transition time in ghost animation

/**
 * @brief Enumeration of ghost types for the animation.
 */
typedef enum {
	GHOST1, GHOST2, GHOST3, GHOST4, GHOST5, GHOST6
} State_GHOT_t;

/* Initialize the ghostType variable to the starting ghost of the animation */

State_GHOT_t ghostType = GHOST1;
/**
 * @brief Clears or turns off all LEDs.
 *
 * This function iterates through all LED addresses and assigns them the off value.
 */
void clear_led(void) {
	assert(led_address != NULL);
	for (int16_t j = INI_ROW_MATRIX; j < ROW_MATRIX; j++) {
		spi_write(led_address[j], clear[j]);
	}
}

/**
 * @brief Initializes the LEDs.
 *
 * This function configures the LEDs and sets their initial values.
 */

void init_led(void) {
	delayInit(&delayGhost, TIMEGHOST);
	spi_init();                  // initializes api_spi
	spi_write(ADDRESS_DECODING, VALUE_DECODING);
	spi_write(ADDRESS_SCAN_LIMIT, VALUE_SCAN_LIMIT);
	spi_write(ADDRESS_POWER, VALUE_POWER);
	spi_write(ADDRESS_TEST_DISPLAY, VALUE_TEST_DISPLAY);
	clear_led();
	spi_write(ADDRESS_BRIGHTNESS, VALUE_BRIGHTNESS);
}

/**
 * @brief Turns on all LEDs.
 *
 * This function iterates through all LED addresses and assigns them the on value.
 */

void lit_led(void) {
	assert(led_address !=NULL);
	for (int16_t j = INI_ROW_MATRIX; j < ROW_MATRIX; j++) {
		spi_write(led_address[j], LitMatrix[j]);
	}
}
/**
 * @brief Updates the state of the LEDs based on a list.
 *
 * This function takes a list of values and updates the state of each LED according to
 * the provided list.
 *
 * @param paint_list List with the LED values.
 */
void update_led(uint8_t paint_list[]) {
	assert(paint_list != NULL);
	for (int16_t j = INI_ROW_MATRIX; j < ROW_MATRIX; j++) {
		spi_write(led_address[j], paint_list[j]);
	}
}

/**
 * @brief Updates the state of the LEDs based on a row.
 *
 * This function takes a list of values and updates the state of each LED according to
 * the provided list.
 *
 * @param paint_list List with the LED values.
 */
void row_led(uint8_t row_led) {
	assert(row_led >= NULLROW);
	for (int16_t j = INI_ROW_MATRIX; j < ROW_MATRIX; j++) {
		spi_write(led_address[j], row_led);
	}
}

/**
 * @brief Generates a ghost animation.
 *
 * This function creates a ghost animation on the LED display.
 *
 * @param void
 */

void ghost_led(void) {
	assert(ghostType >= NULLGHOST);
	switch (ghostType) {
	case (GHOST1):
		update_led(ghost1);
		if (delayRead(&delayGhost)) {
			ghostType = GHOST2;
		}
		break;
	case (GHOST2):
		update_led(ghost2);
		if (delayRead(&delayGhost)) {
			ghostType = GHOST3;
		}
		break;
	case (GHOST3):
		update_led(ghost3);
		if (delayRead(&delayGhost)) {
			ghostType = GHOST4;
		}
		break;
	case (GHOST4):
		update_led(ghost4);
		if (delayRead(&delayGhost)) {
			ghostType = GHOST5;
		}
		break;
	case (GHOST5):
		update_led(ghost5);
		if (delayRead(&delayGhost)) {
			ghostType = GHOST6;
		}
		break;
	case (GHOST6):
		update_led(ghost5);
		if (delayRead(&delayGhost)) {
			ghostType = GHOST1;
		}
		break;
	default:
		/* Handle unexpected state */
		assert(0);
	}
}
