/**
 ******************************************************************************
 * @file
 * @author  Luis Gómez
 * Objetivo : Implementar un módulo de software para trabajar con retardos no bloqueantes
 * que son aplicados a LEDs de la placa STM32F4
 * Crear una carpeta API dentro de la carpeta Drivers en la estructura de directorios
 * del nuevo proyecto. Crear dentro de la carpeta API, subcapetas /Src y /Inc.
 *
 *
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
#include <assert.h>

/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define time 200
#define retardo100 100
#define retardo500 500
#define retardo1000 1000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/



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

	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED1);
	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED2);
	/* Initialize BSP Led for LED1 */
	BSP_LED_Init(LED3);

	/* Estas son las esctructuras que creamos para los 3 leds notar que
	 * delayWrite() podriamos haber cambiado el tiempo de retardo */

    delay_t Delay100;
    delay_t Delay500;
    delay_t Delay1000;

    /* Inicializamos las tres estructuras con distinto tiempo (100,500,1000)*/

    delayInit(&Delay100, retardo100); // Inicializa el retardo a 100 ticks
    delayInit(&Delay500, retardo500); //
    delayInit(&Delay1000, retardo1000); //


	/* Infinite loop */

    while (1) {
        if (delayRead(&Delay100)) { // El retardo se ha cumplido, encender o apagar LED1
        	BSP_LED_Toggle(LED1);

        }
        if (delayRead(&Delay500)) { // El retardo se ha cumplido, encender o apagar LED2
              BSP_LED_Toggle(LED2);

        }
        if (delayRead(&Delay1000)) { // El retardo se ha cumplido, encender o apagar LED3
              BSP_LED_Toggle(LED3);

        }

    }
    return 0;
}
/* delayInit debe cargar el valor de duración del retardo en la estructura, en el campo
correspondiente. No debe iniciar el conteo del retardo. Debe inicializar el flag running
en `false´. */
void delayInit( delay_t * delay, tick_t duration )
{
	assert(delay != NULL);
	assert(delay->duration >=0);
	delay->duration = duration;
	delay->running = false;
}

/*  delayRead debe verificar el estado del flag running.
○ false, tomar marca de tiempo y cambiar running a ‘true’
○ true, hacer la cuenta para saber si el tiempo del retardo se cumplió o no:
‘marca de tiempo actual - marca de tiempo inicial es mayor o igual a duración
del retardo’?
y devolver un valor booleano que indique si el tiempo se cumplió o no.
○
Cuando el tiempo se cumple se debe cambiar el flag running a false.*/

bool_t delayRead( delay_t * delay ){

	bool_t retValue = false;

	assert(delay !=NULL);
	if (delay->running == false){
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}
	else{
		 if((HAL_GetTick()-delay->startTime) >= delay->duration){
			 delay->running = false;
			 retValue = true;
		 }
	}
	return retValue;
}

/*delayWrite permite cambiar el tiempo de duración de un delay existente*/

void delayWrite( delay_t * delay, tick_t duration ){
	assert(delay != NULL);
	assert(delay->duration >=0);
	delay->duration=duration;
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
