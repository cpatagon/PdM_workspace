/**
 * @file API_spi.h
 * @brief Biblioteca para comunicación SPI con el chip MAX7219.
 * @date Aug 6, 2023
 * @author lgomez
 */

#ifndef API_INC_API_SPI_H_
#define API_INC_API_SPI_H_

#include <stdint.h>   /**< Incluye tipos de definición estándar, como uint32_t. */
#include <stdbool.h>  /**< Incluye el tipo booleano (bool). */
#include "main.h"     /**< Archivo principal con configuraciones y prototipos relevantes. */

/** @brief Puerto GPIO definido para la comunicación con MAX7219. */
#define maxport GPIOD
/** @brief Pin de datos (DIN) para el MAX7219. */
#define data_Pin DIN_Pin
/** @brief Pin de selección de chip (CS) para el MAX7219. */
#define cs_Pin CS_Pin
/** @brief Pin de reloj (CLK) para el MAX7219. */
#define clock_Pin CLK_Pin

/** @brief Número de módulos de matriz de puntos (dot-matrix-displays) en uso. */
#define num 1

void spi_init(void);

/**
 * @brief Envia una dirección y un comando al dispositivo MAX7219.
 *
 * @param address Dirección o registro al que se escribirá el comando.
 * @param cmd Comando o dato a ser escrito.
 */
void spi_write(uint8_t address, uint8_t cmd);

#endif /* API_INC_API_SPI_H_ */

