/**
 ******************************************************************************
 * @file    Practice 4 Point 1
 * @author  Luis Gómez
 * @brief   Implement a FSM (Finite State Machine) for software debounce.
 * @task    Create a new project as a copy of the project completed for
 *          practice 3. Implement a software debounce FSM that allows you to read
 *          the state of the NUCLEO-F429ZI board push-button and generate actions or
 *          events against a falling or rising edge, according to the diagram.
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
// FSM state
typedef enum{
    BUTTON_UP,       // Button released
    BUTTON_FALLING,  // Pressing button
    BUTTON_DOWN,     // Button pressed
    BUTTON_RAISING   // Releasing button
} debounceState_t;


/* Private define ------------------------------------------------------------*/
#define TIME1 40 // Time delay or debounce


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief This function initializes the FSM with the defined value at the start of the model
 *
 * @param currentState: a pointer to the current state of the FSM
 * @param initial_state: the initial state of the FSM
 * @retval None
 */
void debounceFSM_init(debounceState_t*, debounceState_t);		// debe cargar el estado inicial

/**
 * @brief This function reads inputs, manages the transition between states,
 * and updates the outputs accordingly.
 * The input is the currentState of button and debounce delay
 * the output is the change the states and that LED1 and LED2
 *
 * @param currentState: a pointer to the current state of the FSM
 * @param delay: a pointer to the delay instance
 * @retval None
 */
void debounceFSM_update(debounceState_t*, delay_t* );	// debe leer las entradas, resolver la lógica de
					// transición de estados y actualizar las salidas
/**
 * @brief This function toggles the state of LED1
 *
 * @param None
 * @retval None
 */
void buttonPressed();			// debe invertir el estado del LED1

/**
 * @brief This function toggles the state of LED3
 *
 * @param None
 * @retval None
 */
void buttonReleased();		// debe invertir el estado del LED3

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
	/* STM32F4xx HAL library initialization */
	SystemClock_Config();

	/*Inicialisamos variables */

	/* Initialize LED and BSP PB for
	 * BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED3);

	 /* Initialize variables */

	/* Declaramos variable que contendrá el
	 * tiempo de retardo*/
	delay_t Delay1;

    /* definimos la variable que contendra el estado del modelo*/
	debounceState_t Estado;

	/* definimos el estado inicial de modelo como BUTTON_UP*/
	debounceFSM_init(&Estado, BUTTON_UP);

   /* Inicializa el retardo en 40 ms */
	delayInit(&Delay1, TIME1);

	/* Infinite loop */
    while (1) {
    	/* llamamos a la función que evaluara el estado de
    	 * nuestro modelo MEF*/
    	debounceFSM_update(&Estado,&Delay1);
    }
    return 0;
}
/* funciones propias
 *
 * Función Inicializar MEF con el valor definido
 * en el inicio del modelo
 * */

void debounceFSM_init(debounceState_t * EstadoActual, debounceState_t Valor){
	/* Initialize Estado */
	*EstadoActual=Valor;
}

/**
 * @brief   Manages the transitions of the debounce FSM.
 *          This function reads the inputs (current state of the button and debounce delay),
 *          evaluates the transition conditions according to the FSM's current state,
 *          and updates the current state and outputs (LED1 and LED3) accordingly.
 *
 * @param   currentState: pointer to the current state of the FSM
 * @param   delay: pointer to the delay instance
 * @retval  None
 */
void debounceFSM_update(debounceState_t * currentState, delay_t* delay){
	switch (*currentState){
	/*
	 * In the BUTTON_UP state, it checks whether the button remains unpressed.
	 * Otherwise, that is, if the button is pressed, the state changes to BUTTON_FALLING.
	 */
	case BUTTON_UP:
		// Checks if the button has been pressed and, if so, transitions to the BUTTON_FALLING state
		if (BSP_PB_GetState(BUTTON_USER)){
	    	*currentState=BUTTON_FALLING;
		}
		break;
		/*
		 * In the BUTTON_FALLING state, it checks if the button remains pressed for 40 ms.
		 * If it remains pressed (condition 'yes'), the state changes to BUTTON_DOWN and the
		 * state of LED1 is toggled. If the button does not remain pressed (condition 'no'),
		 * the state changes back to BUTTON_UP, interpreting this event as a bounce.
		 */
	case BUTTON_FALLING:
		if (BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
	    	*currentState=BUTTON_DOWN;
	    	buttonPressed();
		}
		else {
			*currentState=BUTTON_UP;
		}
		break;
	/*
	 * In the BUTTON_DOWN state, if the button is released, the state changes to BUTTON_RAISING.
	 */
	case BUTTON_DOWN:
		if (!BSP_PB_GetState(BUTTON_USER)){
	    	*currentState=BUTTON_RAISING;
		}
		break;
	/*
	 * In the BUTTON_RAISING state, it checks if the button remains unpressed for a certain delay.
	 * If it remains unpressed (condition 'yes'), the state changes back to BUTTON_UP and
	 * the buttonReleased function is called. If the button is pressed again (condition 'no'),
	 * the state changes back to BUTTON_DOWN.
	 */
	case BUTTON_RAISING:
		if (!BSP_PB_GetState(BUTTON_USER) && delayRead(delay)){
	    	*currentState=BUTTON_UP;
	    	buttonReleased();
		}
		else {
			*currentState=BUTTON_DOWN;
		}
		break;
	default:
			/* Handle unexpected state */
		Error_Handler();
	}
	return;
}

/**
 * @brief   Toggles the state of LED1.
 *          When this function is called, it switches the state of LED1 from ON to OFF or vice versa.
 *
 * @param   None
 * @retval  None
 */
void buttonPressed(){
	BSP_LED_Toggle(LED1);
	return;
}
/**


 * @brief   Toggles the state of LED3.
 *          When this function is called, it switches the state of LED3 from ON to OFF or vice versa.
 *
 * @param   None
 * @retval  None
 */
void buttonReleased()
{
	BSP_LED_Toggle(LED3);
	return;
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
