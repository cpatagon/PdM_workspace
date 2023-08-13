/*
 * API_led.h
 *
 *  Created on: Aug 6, 2023
 *      Author: lgomez
 *
 */

/*
 * Librería encargada de manipular la matriz de led 8x8
 * con el CI MAX7219ENG. Mediante un protocolo spi
 * con distintas funciones:
 *
 * - init_led()   = de inicialización
 * - clear_led()  = todos los led apagados
 * - lit_led()    = todos los led encendidos
 * - update_led() = grafica una imagen
 *
 * Toda la comunicación se realiza mediante el protocolo spi
 * implementado en la libreria API_spi.h
 *
 * Tabien se inlcuye un conjunto imagenes prediseñadas listas para
 * ser ocupadas en update_led()
 * */

#ifndef API_INC_API_LED_H_
#define API_INC_API_LED_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* @brief  	conjunto de listas orientados a generar figuras sobre la
 * 			matriz led. Los valores representan una fila dentro de la matriz
 * 			LED
 * */
//static uint8_t led_ocho[] = { 0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x3C }; // 8
static uint8_t smileyFace[] = { 0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C }; // cara feliz
//static uint8_t badFace[] = { 0x00, 0x66, 0x66, 0x00, 0x18, 0x42, 0x3C, 0x00 }; // Cara Triste
static uint8_t A[] = { 0x00, 0x7c, 0x12, 0x12, 0x12, 0x12, 0x7c, 0x00 }; // Letra A
static uint8_t B[] = { 0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x34, 0x00 }; // Letra B
static uint8_t C[] = { 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x24, 0x00 }; // Letra C
static uint8_t cero[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t uno[] = { 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0 };
static uint8_t dos[] = { 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0 };
static uint8_t tres[] = { 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC };
static uint8_t four[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
static uint8_t heart[] = { 0x0C, 0x1E, 0x3E, 0x7C, 0x3E, 0x1E, 0x0C, 0x00 };
static uint8_t *levels_led[] = { cero, uno, dos, tres, four, heart };

/* @brief  	función encargada de inicializar la matriz
 * 			led
 * @param 	void
 * @retval  void
 * */
void init_led(void);

/* @brief  	función encargada de limpiar la pantalla
 * 			led dejado todos los valores de la matriz a 0
 * @param 	void
 * @retval  void
 * */
void clear_led(void);

/* @brief  	función encargada encender todos los led
 * 			de la matriz
 * @param 	void
 * @retval  void
 * */
void lit_led(void);

/* @brief  	función encargada encender los led de acuerdo
 * 			a la figura entregada en forma de lista
 * @param 	paint_list[] lista donde cada fila representa
 * 			un valor de una fila escrita en forma hexadecimal de una
 * 			representación binaria de la fila en donde 0 es led apagado
 * 			y 1 es led encendido
 * @retval  void
 * */
void update_led(uint8_t paint_list[]);

/**
 * @brief Actualiza el estado de los LEDs basándose una fila.
 *
 * Esta función toma una lista de valores y actualiza el estado de cada LED según
 * la lista proporcionada.
 *
 * @param paint_list Lista con los valores de los LEDs.
 */
void fila_led(uint8_t fila);

/**
 * @brief generra una animacion de fantasma.
 *
 * Esta función genera una función de fantasma en la patalla led
 *
 *
 * @param vacio
 */
void fantasma_led(delay_t *delay_Ghost);

#endif /* API_INC_API_LED_H_ */
