/**
  ******************************************************************************
  * @file    Practica05_p2
  * @author  Luis Gómez
  * @brief   Implementar un módulo de software sencillo para trabajar con la UART.
  *  Sobre el ejercicio de la práctica 4, implementar un programa que utilice el
  *  módulo de uart para informar al usuario cuando se producen los flancos ascendente
  *  y descendente.
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
#include "API_uart.h"
#include "API_delay.h"
#include "API_debounce.h"
#include <string.h>


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
#define TIME1 40 // TIEMPO antirrebote
#define TIME2 100 // TIEMPO parpadeo 1
#define TIME3 500 // TIEMPO parpadeo 2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declaration */
//UART_HandleTypeDef UartHandle;

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
  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  /* Initialize BSP Led for LED2 and LED3*/
  BSP_LED_Init(LED1); // Initializes UART
  BSP_LED_Init(LED2); // Function program
  BSP_LED_Init(LED3); // Error not Initializes UART F


  /* Initializes debounce finite state machine (FSM) */
  debounceFSM_init();

	 /* Declares delay variables */
    delaydebounce_t Delay1;
	delay_t Delay2;
	delay_t Delay3;

  /* Initializes the delay to 40 ms, 100 ms, and 500 ms respectively */
  delayInitD(&Delay1, TIME1);
  delayInit(&Delay2, TIME2);
  delayInit(&Delay3, TIME3);


   // Inicialización de la UART utilizando la biblioteca creada
   if (uartInit() != true) {
       // Manejo de error si la inicialización no fue exitosa
       Error_Handler();
   }
   else{
	   BSP_LED_Toggle(LED1); // LED 1 que indica que se inicialiso las trasnmición UART correctamente
   }

   char *status;


   /* Probamos que la función uartSendStringSize()
    * es capaz de enviar una cantidad de caracteres definidos
    * en sizeToSend */

   uint8_t myString[] = "Hello, World!"; // frase enviada al UART
   uint16_t sizeToSend = strlen((char *)myString) / 2; // calcula la mitad de su tamaño
   uartSendStringSize(myString, sizeToSend);    // envia la frase completa y la cantidad de caracteres que se quiere imprimir



  /* Infinite loop */
  while (1)
  {
	  /* Calls debounce FSM update function. If the button is pressed for a duration
	      	 * longer than the debounce delay (Delay1), it will change the state of the FSM.
	      	 * This also results in a change in the return of the readKey() function from
	      	 * true -> false or from false to true each time a valid BUTTON_FALLING is detected.
	      	 * */
	        debounceFSM_update(&Delay1);
	        // Imprime cuando ocurre un cambio
	      	if (status != readStatus()){
      			status=readStatus(); //lee estatus del pulsador
      			uartSendString(status); // envía estatus al puerto con UART
	      	}
	          /* If the state of readKey() changes to false or true as a result of pressing
	           * a button validly according to the debounce rules, it will trigger a change
	           * in the blink frequency of LED2.
	           * */
	      	if (readKey()){
	      		if (delayRead(&Delay2)){
	      			BSP_LED_Toggle(LED2); // Toggles LED2 with a blink frequency determined by Delay2
	      		}
	      	}
	      	else{
	      		if (delayRead(&Delay3)){
	      			BSP_LED_Toggle(LED2); // Toggles LED2 with a blink frequency determined by Delay3
	      			BSP_LED_Off(LED1); // apaga LED 1 que indica que se inicialiso la trasnmición UART
	      		}
	      	}
	      }
	      return 0;
}



/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
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
  BSP_LED_On(LED3);
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
