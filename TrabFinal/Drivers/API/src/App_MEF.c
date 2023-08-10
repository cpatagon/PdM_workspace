/*
 * App_MEF.c
 *
 *  Created on: Aug 6, 2023
 *      Author: lgomez
 */

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#include <assert.h>
#include "App_MEF.h"

State_MEF_t estadoMEF;

void inicializarMEF(void){
	/* Initialize Estado */
	estadoMEF=SET;
	return;
};

State_MEF_t actualizarMEF(delay_t * delay){
		assert(&estadoMEF!=NULL);
		switch (estadoMEF){
		case SET_ini:
			if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
			    	estadoMEF=FIRST;
				}
			break;
		case FIRST:
			if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
				    	estadoMEF=SECOND;
					}
			else if(BSP_PB_GetState(BUTTON_USER) && !delayRead(delay)){
				estadoMEF=BAD;
			}
			break;
		case SECOND:
			if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
				    	estadoMEF=THIRD;
					}
			else if(BSP_PB_GetState(BUTTON_USER) && !delayRead(delay)){
					estadoMEF=BAD;
				}
			break;
		case THIRD:
			if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
				estadoMEF=FIRST;
			}
			else if(BSP_PB_GetState(BUTTON_USER) && !delayRead(delay)){
					estadoMEF=GOOD;
				}
			break;
		case GOOD:
			if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
				estadoMEF=SET;
			}

			break;
		case BAD:
			if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
				estadoMEF=SET;
			}

			break;
		default:
				/* Handle unexpected state */
			assert(0);
		}
 return(estadoMEF);
};

//char *Lee_estado(){};
