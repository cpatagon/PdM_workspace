/**
 ******************************************************************************
 * @file
 * @author  Luis Gómez
 * Objetivo : Implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2.
 * Implementar un programa que utilice retardos no bloqueantes y haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de acuerdo a una secuencia predeterminada como en la práctica 1.
 * Cada led debe permanecer encendido 200 ms.  No debe encenderse más de un led simultáneamente en ningún momento.
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


/** @addtogroup STM32F4xx_HAL_Examples
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define time 200
#define TIME1 200 // TIEMPO ESPERA LED1
#define ON 1
#define OFF 0
#define PRIMERO 1 // LED1
#define SEGUNDO 2 // LED2
#define TERCERO 3 // LED3
#define LED_init PRIMERO // LED INICIAL LED1

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

    delay_t Delay1;

    /* Inicializamos las tres estructuras con distinto tiempo (100,500,1000)*/

    delayInit(&Delay1, TIME1); // Inicializa el retardo a 100 ticks

    int LED_select = LED_init; // LED inicial
    int Estado_LED = OFF ; // EStado de LED  inicial


	/* Infinite loop */
    while (1) {
    	if (delayRead(&Delay1)){
        if (LED_select == PRIMERO) { // El retardo se ha cumplido, encender o apaga LED1
        	if (Estado_LED == OFF){ // se prende el led 1 y se mantiene en LED 1
        		BSP_LED_On(LED1);
        		Estado_LED = ON;
        		LED_select = PRIMERO;
        	}
        	else{ // la segunda vez que pasa apaga el LED 1 y selecciona el LED2 para encender
        		BSP_LED_Off(LED1);
        		LED_select = SEGUNDO;
        		Estado_LED = OFF;
        	}
        }
        if (LED_select == SEGUNDO ) { // El retardo se ha cumplido, encender o apaga LED2
        	if (Estado_LED == OFF){ // Enciende LED2
        		BSP_LED_On(LED2);
        		Estado_LED = ON;
        		LED_select = SEGUNDO;
        	}
        	else{ // APAGA LED2 y Seleciona LED3
        		BSP_LED_Off(LED2);
        		LED_select = TERCERO;
        		Estado_LED = OFF;
        	}
        }
        if (LED_select == TERCERO) { // El retardo se ha cumplido, encender o apagar LED3
        	if (Estado_LED == OFF){ // Enciende LED3
        		BSP_LED_On(LED3);
        		Estado_LED = ON;
        		LED_select = TERCERO;
        	}
        	else{ // APAGA LED3 y Seleciona LED1
        		BSP_LED_Off(LED3);
        		LED_select = PRIMERO;
        		Estado_LED = OFF;
        	}
        }
        }
    }
    return 0;
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
