/**
 * @file API_spi.h
 * @brief Library for SPI communication with the MAX7219 chip.
 * @date Aug 6, 2023
 * @author lgomez
 * 
 * 	Library responsible for initializing and writing to the selected GPIO ports 
 * 	using the SPI protocol. Configuration should be done using the STM32CubeIDE 
 * 	for the Nucleo, setting the GPIO ports as DIN_Pin for MOSI, CS_Pin for CS, and CLK_Pin
 * 	for the SPI communication clock.
 * 
 * 
 */

#ifndef API_INC_API_SPI_H_
#define API_INC_API_SPI_H_

#include <stdint.h>   /**< Includes standard definition types, such as uint32_t. */
#include <stdbool.h>  /**< Includes the boolean type (bool). */
#include "main.h"     /**< Main file with relevant configurations and prototypes. */

/** @brief GPIO port defined for communication with MAX7219. */
#define maxport GPIOD
/** @brief MOSI (or DIN) data pin for the MAX7219. */
#define data_Pin DIN_Pin
/** @brief Chip Select (CS) pin for the MAX7219. */
#define cs_Pin CS_Pin
/** @brief Clock (CLK) pin for the MAX7219. */
#define clock_Pin CLK_Pin
/** @brief Number of dot matrix modules in use. */
#define num 1
/**
 * @brief Function to initialize the SPI protocol.
 *
 */
void spi_init(void);

/**
 * @brief Sends an address and a command to the MAX7219 device.
 *
 * @param address Address or register to which the command will be written.
 * @param cmd Command or data to be written to memory.
 */
void spi_write(uint8_t address, uint8_t cmd);

#endif /* API_INC_API_SPI_H_ */

