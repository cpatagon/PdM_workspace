/**
 * @file API_spi.c
 * @brief Implementación de funciones para manejo manual del protocolo SPI en STM32F4xx.
 * @date Aug 6, 2023
 * @author lgomez
 */

#include <stdint.h>  ///< Incluye tipos de definición estándar, como uint32_t.
#include <stdbool.h> ///< Incluye el tipo booleano (bool).
#include "API_spi.h"

/**
 * @brief Funcion de Inicialización GPIO.
 *
 * @param nada.
 *
 */
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void spi_write_byte(uint8_t);

void spi_init(void) {
	MX_GPIO_Init();
	MX_SPI3_Init();
}

SPI_HandleTypeDef hspi3;

/**
 * @brief Envía un byte de datos utilizando el protocolo SPI manualmente.
 *
 * Esta función realiza operaciones bit a bit para transmitir un byte de datos
 * utilizando el protocolo SPI. No utiliza las capacidades de hardware SPI del
 * microcontrolador (HAL), sino que implementa la transmisión manualmente.
 *
 * @param byte Byte de datos que se desea enviar a través de SPI.
 *
 */
static void spi_write_byte(uint8_t byte) {
	// Itera a través de cada uno de los 8 bits del byte proporcionado.
	for (uint8_t i = 0; i < 8; i++) {
		// Establece el pin del reloj (clock) en estado bajo.
		HAL_GPIO_WritePin(maxport, clock_Pin, 0);

		// Escribe el bit más significativo (MSB) del byte en el pin de datos (data).
		HAL_GPIO_WritePin(maxport, data_Pin, byte & 0x80);

		// Desplaza el byte a la izquierda para preparar el siguiente bit.
		byte = byte << 1;

		// Establece el pin del reloj (clock) en estado alto.
		HAL_GPIO_WritePin(maxport, clock_Pin, 1);
	}
}

/**
 * @brief Envía una dirección y un comando utilizando el protocolo SPI manualmente.
 *
 * Esta función envía un byte de dirección seguido de un byte de comando utilizando
 * el protocolo SPI. La función envía el par de bytes (dirección y comando)
 * múltiples veces según el valor predefinido de 'num'.
 *
 * @param address Byte de dirección que se desea enviar a través de SPI.
 * @param cmd Byte de comando que se desea enviar a través de SPI.
 */
void spi_write(uint8_t address, uint8_t cmd) {
	// Establece el pin CS (Chip Select) en estado bajo.
	HAL_GPIO_WritePin(maxport, cs_Pin, 0);

	// Envía el par de bytes (dirección y comando) 'num' veces.
	for (uint8_t i = 0; i < num; i++) {
		// Envía el byte de dirección.
		spi_write_byte(address);

		// Envía el byte de comando.
		spi_write_byte(cmd);
	}

	// Establece el pin CS (Chip Select) en estado bajo.
	HAL_GPIO_WritePin(maxport, cs_Pin, 0);

	// Establece el pin CS (Chip Select) en estado alto.
	HAL_GPIO_WritePin(maxport, cs_Pin, 1);
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
