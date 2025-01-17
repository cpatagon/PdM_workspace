/**
 * @file API_spi.c
 * @brief Implementation of functions for manual management of the SPI protocol in STM32F4xx.
 * @date Aug 6, 2023
 * @author lgomez
 */

#include <stdint.h>  ///< Includes standard definition types, such as uint32_t.
#include <stdbool.h> ///< Includes the boolean type (bool).
#include "API_spi.h"

#define STATE_HIGH 1
#define STATE_LOW 0
#define SIGNIFICANT_BIT 0x80
#define NEXT_BIT 1
#define NUM_BITS 8
#define NUM_BITS_INI 0
#define MATRIX_INI 0

/**
 * @brief GPIO Initialization Function.
 *
 * @param void.
 *
 */
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void spi_write_byte(uint8_t);

void spi_init(void) {
	MX_GPIO_Init();
	MX_SPI3_Init();
}

static SPI_HandleTypeDef hspi3;

/**
 * @brief Sends a byte of data using the SPI protocol manually.
 *
 * This function performs bit-by-bit operations to transmit a byte of data
 * using the SPI protocol. It doesn't utilize the microcontroller's hardware SPI
 * capabilities (HAL) but instead implements the transmission manually.
 *
 * @param byte The byte of data intended to be sent through SPI.
 *
 */
static void spi_write_byte(uint8_t byte) {
	assert_param(byte);
	// Iterates through each of the 8 bits of the provided byte.
	for (uint8_t i = NUM_BITS_INI; i < NUM_BITS; i++) {
		// Sets the clock pin to a low state.
		// which establishes the sending of a byte.
		HAL_GPIO_WritePin(MAXPORT, CLOCK_PIN, STATE_LOW);
		// According to the IC requirements, sends the most
		// significant bit (MSB) of the byte on the data pin (MOSI).
		HAL_GPIO_WritePin(MAXPORT, DATA_PIN, byte & SIGNIFICANT_BIT);
		// Shifts the byte to the left to prepare the next bit.
		// This ensures the sending from the most significant bit
		// to the least significant according to the employed IC.
		byte = byte << NEXT_BIT;
		// Sets the clock pin to a high state
		// indicating the completion of the bit's transmission.
		HAL_GPIO_WritePin(MAXPORT, CLOCK_PIN, STATE_HIGH);
	}
}

/**
 * @brief Sends an address and a command using the SPI protocol manually.
 *
 * This function sends a byte of address followed by a byte of command
 * using the SPI protocol. The function sends the pair of bytes (address
 * and command) multiple times based on the predefined value of 'num'
 * (number of LED screens). It is recommended to consult the datasheet
 * of the MAX7219 IC.
 *
 * @param address Byte of address intended to be sent through SPI.
 * @param cmd Byte of command intended to be sent through SPI.
 */
void spi_write(uint8_t address, uint8_t cmd) {
	assert_param(address != NULL);
	assert_param(cmd != NULL);
	/** Sets the CS (Chip Select) pin to a low state to
	 * initiate communication with the connected slave device
	 * at port cs_Pin via the CS cable. */
	HAL_GPIO_WritePin(MAXPORT, CS_PIN, STATE_LOW);
	/** Sends the pair of bytes (address and command) 'num' times
	 * in case there are multiple screens. */
	for (uint8_t i = MATRIX_INI; i < NUM_MATRIX; i++) {
		/* Sends the address byte to the LED IC indicating the action.
		 * These actions can range from turning on a specific row to
		 * defining the brightness of the LEDs. */
		spi_write_byte(address);
		/* Sends the command byte detailing what to do at the previously
		 * specified address, defining what action to take at that memory position. */
		spi_write_byte(cmd);
	}
	/** Sets the CS (Chip Select) pin to low, indicating
	 * the communication will end. */
	HAL_GPIO_WritePin(MAXPORT, CS_PIN, STATE_LOW);
	/* Sets the CS (Chip Select) pin to high, freeing
	 * the slave. */
	HAL_GPIO_WritePin(MAXPORT, CS_PIN, STATE_HIGH);
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LD1_Pin | LD3_Pin | GPIO_PIN_5 | LD2_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, CS_Pin | DIN_Pin | CLK_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOG, USB_PowerSwitchOn_Pin | GPIO_PIN_15,
			GPIO_PIN_RESET);

	/*Configure GPIO pin : USER_Btn_Pin */
	GPIO_InitStruct.Pin = USER_Btn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : LD1_Pin LD3_Pin LD2_Pin */
	GPIO_InitStruct.Pin = LD1_Pin | LD3_Pin | LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : CS_Pin DIN_Pin CLK_Pin */
	GPIO_InitStruct.Pin = CS_Pin | DIN_Pin | CLK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pins : USB_PowerSwitchOn_Pin PG15 */
	GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pin : USB_OverCurrent_Pin */
	GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : PB5 */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/**
 * @brief SPI3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI3_Init(void) {

	/* USER CODE BEGIN SPI3_Init 0 */

	/* USER CODE END SPI3_Init 0 */

	/* USER CODE BEGIN SPI3_Init 1 */

	/* USER CODE END SPI3_Init 1 */
	/* SPI3 parameter configuration*/
	hspi3.Instance = SPI3;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi3.Init.NSS = SPI_NSS_HARD_OUTPUT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi3.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI3_Init 2 */

	/* USER CODE END SPI3_Init 2 */

}
