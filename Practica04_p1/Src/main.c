/**
 ******************************************************************************
 * @file Práctica 4 Punto 1
 * @author  Luis Gómez
 * Objetivo : Implementar un MEF para trabajar con anti-rebotes por software.
 * @ actividad : Crear un nuevo proyecto como copia del proyecto realizado para
 * la práctica 3.
 * Implementar una MEF anti-rebote que permita leer el estado del pulsador de la
 * placa NUCLEO-F429ZI y generar acciones o eventos ante un flanco descendente
 * o ascendente, de acuerdo al diagrama
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Ve el estado de la variable
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
*/

typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RAISING,
} debounceState_t;

/* Private define ------------------------------------------------------------*/
#define time 200
#define TIME1 40 // TIEMPO ESPERA O RETARDO


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

void debounceFSM_init(debounceState_t*, debounceState_t);		// debe cargar el estado inicial
void debounceFSM_update(debounceState_t*, delay_t* );	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
void buttonPressed();			// debe invertir el estado del LED1
void buttonReleased();		// debe invertir el estado del LED3

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
	/* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
	 */


	//HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/*Inicialisamos variables */

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED3);

	delay_t Delay1;

	debounceState_t Estado;

	//Estado = BUTTON_UP;
	debounceFSM_init(&Estado, BUTTON_UP);


	/* Estas son las esctructuras que creamos para los 3 leds notar que
	 * delayWrite() podriamos haber cambiado el tiempo de retardo */

    //delay_t Delay1;

    /* Inicializamos las tres estructuras con distinto tiempo (100,500,1000)*/

   // delayInit(&Delay1, TIME1); // Inicializa el retardo a 100 ticks


	//void debounceFSM_init();
	delayInit(&Delay1, TIME1);

	/* Infinite loop */
    while (1) {
    	//debounceFSM_update();
    	debounceFSM_update(&Estado,&Delay1);
    }
    return 0;
}


/* funciones propias
 *
 * // Función Inicializar MEF
void inicializarMEF(void){
	 estadoActual = ESTADO_INICIAL;
    // Resto de la inicializaciones
 * */
// debe cargar el estado inicial


/**
  * @brief  Configura estados del boton.
  * @param  Booton: esecifica el boton para ser configurado
  *   This parameter can be one of following parameters:
  *     @arg  LED1
  *     @arg  LED2
  *     @arg  LED3
  */
void debounceFSM_init(debounceState_t * EstadoActual, debounceState_t Valor){
	/* Initialize Estado */
	*EstadoActual=Valor;
}

void debounceFSM_update(debounceState_t * EstadoActual, delay_t* delay){
	switch (*EstadoActual){
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER)){
	    	*EstadoActual=BUTTON_FALLING;
		}
		break;
	case BUTTON_FALLING:
		if (BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
	    	*EstadoActual=BUTTON_DOWN;
	    	buttonPressed();
		}
		else {
			*EstadoActual=BUTTON_UP;
		}
		break;
	case BUTTON_DOWN:
		if (!BSP_PB_GetState(BUTTON_USER)){
	    	*EstadoActual=BUTTON_RAISING;
		}
		break;
	case BUTTON_RAISING:
		if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
	    	*EstadoActual=BUTTON_UP;
	    	buttonReleased();
		}
		else {
			*EstadoActual=BUTTON_DOWN;
		}
	}
}

	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas



void buttonPressed(){			// debe invertir el estado del LED1
	BSP_LED_Toggle(LED1);
}

void buttonReleased()	// debe invertir el estado del LED3
{
	BSP_LED_Toggle(LED3);
}


static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	if(HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}



/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/