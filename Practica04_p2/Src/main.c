/**
 ******************************************************************************
 * @file Práctica 4 Punto 2
 * @author  Luis Gómez
 * @Hardware: STM32F429ZI
 * @Objetivo: Implementar un programa que cambie la
 *      frecuencia de toggleo del LED2 entre 100 ms y 500
 *      ms cada vez que se presione la tecla.  El programa
 *      debe usar las funciones anti-rebote del módulo API
 *      debounce y los retardos no bloqueantes del módulo
 *      API_delay.
 *
 *//*
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
typedef enum{
	PRIMERO, // primera frecuancia
	SEGUNDO, // segunda frecuencia
} estadofrecuencia_t;

/* Private define ------------------------------------------------------------*/
#define TIME1 40 // TIEMPO antirrebote
#define TIME2 100 // TIEMPO parpadeo 1
#define TIME3 500 // TIEMPO parpadeo 2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

void frecuencia_update(estadofrecuencia_t *,delay_t*,delay_t*,Led_TypeDef);

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

	/*Inicialisamos variables */

	/* Initialize LED and BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);

	/* Declaramos variable que contendrá el tiempo de retardo*/
	delay_t Delay1;
	delay_t tiempo1;
	delay_t tiempo2;


    /* definimos la variable que contendra el estado del modelo*/
	debounceState_t Estado;

	estadofrecuencia_t Estado_f;

	Estado_f=PRIMERO;

	/* definimos el estado inicial de modelo como BUTTON_UP*/
	debounceFSM_init(&Estado, BUTTON_UP);

   /* Inicializa el retardo en 40 ms */
	delayInit(&Delay1, TIME1);
	delayInit(&tiempo1, TIME2);
	delayInit(&tiempo2, TIME3);

	/* Infinite loop */
    while (1) {
    	/* llamamos a la función que evaluara el estado de
    	 * nuestro modelo MEF*/
    	debounceFSM_update(&Estado,&Delay1);

    	//frecuencia_update(&Estado_f,&tiempo1,&tiempo2,LED2);
    	if (readKey()){
    		if (delayRead(&tiempo1)){
    			BSP_LED_Toggle(LED2);
    		}
    	}
    	else{
    		if (delayRead(&tiempo2)){
    			BSP_LED_Toggle(LED2);
    		}
    	}
    }
    return 0;
}

/* FIN FUNCIONES PROPIAS */


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
