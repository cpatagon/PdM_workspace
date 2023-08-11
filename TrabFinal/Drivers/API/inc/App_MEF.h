/*
 * App_MEF.h
 *
 *  Created on: Aug 6, 2023
 *      Author: lgomez
 */

#ifndef API_INC_APP_MEF_H_
#define API_INC_APP_MEF_H_

//#include "API_led.h"
#include "API_delay.h" /* Inclusion of the file defining delay_t */
#include "API_debounce.h"

typedef enum{
	SET_ini,
	FIRST,
	SECOND,
	THIRD,
	GOOD,
	BAD
} State_MEF_t;

void inicializarMEF(void);

State_MEF_t actualizarMEF(delay_t *delay);

//char *Lee_estado();

#endif /* API_INC_APP_MEF_H_ */
