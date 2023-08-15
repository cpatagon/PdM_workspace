/**
 * @file App_MEF.h
 * @brief Definiciones y prototipos de funciones para la máquina de estados finitos (MEF) de la aplicación.
 * @date Aug 6, 2023
 * @author lgomez
 */

#ifndef API_INC_APP_MEF_H_
#define API_INC_APP_MEF_H_

//#include "API_led.h"
#include "API_delay.h"       /**< Inclusión del archivo que define delay_t. */
#include "API_debounce.h"    /**< Inclusión de la biblioteca para gestionar el rebote de botones. */

/**
 * @brief Enumeración de los posibles estados de la MEF.
 */
typedef enum {
	SET_ini, /**< Estado inicial de la MEF. */
	FIRST, /**< Primer estado después del inicio. */
	SECOND, /**< Segundo estado. */
	THIRD, /**< Tercer estado. */
	GOOD, /**< Estado de 'bueno'. */
	BAD /**< Estado de 'malo'. */
} State_MEF_t;

/**
 * @brief Inicializa la máquina de estados finitos.
 */
void init_MEF(void);

/**
 * @brief Actualiza el estado actual de la MEF basado en entradas y condiciones.
 *
 * @param delay Puntero a la estructura de retardo.
 * @return State_MEF_t: El estado actualizado de la MEF.
 */
State_MEF_t update_MEF(delay_t *delay);

/**
 * @brief Lee y retorna el estado actual de la MEF.
 *
 * @note Esta función está actualmente incompleta y debe ser implementada.
 *
 * @return char*: Una representación en cadena del estado actual.
 */
//char *Lee_estado();
#endif /* API_INC_APP_MEF_H_ */

