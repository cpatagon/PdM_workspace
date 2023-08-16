/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 ******************************************************************************
 * @author         : Luis Gómez (lgomez)
 * @file           : main.c
 * @date           : 2023-08-16
 * @brief          : SKILL AND TIMING GAME WITH STM32
 *
 * 	The primary goal of this project is to develop an electronic game that
 * 	indicates to the user whether they have pressed a button at the right time.
 * 	Depending on the player's accuracy, the response can be good or bad.
 * 	To carry out the work, commercial NUCLEO boards (STM32-F429ZI) will be used,
 * 	along with an LED matrix board with the integrated MAX7219 circuit (Maxim2023).
 * 	The game's state information will be displayed on an LED matrix screen.
 *
 * @attention 		: NUCLEO boards (STM32-F429ZI) and integrated (MAX7219) circuit
 *
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdint.h>  /* this is to include the uint32_t types */
#include "main.h"
#include "string.h" /* library for string handling */
#include "API_delay.h" /* library responsible for handling delay times */
#include "API_led.h" /* library in charge of managing the LED display */
#include "App_MEF.h" /* library responsible for loading the finite state model (FSM) of the game */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* *
 * @brief Game speed and score configuration parameters
 * game speeds; the smaller the value, the faster it is
 */
#define SPEED1 1000 // minimum speed
#define SPEED2 800
#define SPEED3 500
#define SPEED4 400 // maximum speed
#define SCORE_INI 0 // initial score value
#define SCORE_MAX 5 // maximum score value
#define LEVEL_MIN 0 // value of the initial level position of the game speed
#define LEVEL_MAX 3 // value of the initial level position of the game speed

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

ETH_TxPacketConfig TxConfig;
ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

ETH_HandleTypeDef heth;
UART_HandleTypeDef huart3;
PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */

/**
 * @ brief declaration and initialization of game variables
 *
 * 	For example, speeds, initial and
 * 	maximum scores, a flag that prevents the score from
 * 	being incremented twice, etc.
 * 	we initialize the variables that will contain the times
 *
 *  */
// variable that handles the transition times (speeds) between states of the FSM (game)
static delay_t Delay_play;
// initialization of state variables of the finite state model FSM that controls the game
static State_MEF_t state_FSM;
// variable (type list) that contains the different game speeds according to the game level
const static tick_t level[] = { SPEED1, SPEED2, SPEED3, SPEED4 };
// we initialize the game's point counter
static int16_t score = SCORE_INI;
// we set the minimum value to the value with which the game will start
static int16_t level_i = LEVEL_MIN;
// we create a variable that indicates the speed of the game
static tick_t speed_play;
// this flag is to prevent the score or speed from being incremented twice
static bool_t flag;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

static void MX_ETH_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief Level Speed Update Function
 *
 * 		Function that controls the game delay speed
 * 		according to the previously set configuration.
 *
 * @param speed level position (int16_t)
 * @retval returns the updated speed level value (int16_t)
 */
static int16_t level_speed_update(int16_t);

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/**
	 * We initialize some variables related to
	 * the states of the FSM and the flag that prevents
	 * counting the speed and score increase twice.
	 */
	state_FSM = SET_ini;              // We define the initial state
	flag = true;

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/**
	 * @brief Initialize some functions and libraries
	 *
	 * Initialize the game's Finite State Machine (FSM).
	 * This function sets up the initial state and prepares it
	 * to be properly initialized.
	 */
	init_MEF();

	/* We initialize the API_spi library that controls the operation
	 * of the 8x8 LED screen */
	init_led();

	/* We define the Delay speed at the initial level, which is the
	 * slowest according to the delay */
	speed_play = level[LEVEL_MIN]; // we set the speed to the minimum level;
	delayInit(&Delay_play, speed_play);

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */

	MX_ETH_Init();
	MX_USART3_UART_Init();
	MX_USB_OTG_FS_PCD_Init();

	/* USER CODE BEGIN 2 */

	// calculamos el numero maximo de velocidaddes que con que establecio el juego
	//level_max = (int16_t) (sizeof(level) / sizeof(level[0]));
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

		/* *
		 * Update the Finite State Machine and get the
		 * current state, which can be SET_ini (score update),
		 * FIRST (A), SECOND (B), THIRD (C), GOOD (smiley face) or BAD (ghost).
		 * */
		state_FSM = update_MEF(&Delay_play);
		// To prevent the score from overflowing
		if (score > SCORE_MAX) {
			score = SCORE_INI;
		}

		/* Depending on the current state, display a specific
		 * pattern or image on the LED matrix.
		 * */
		switch (state_FSM) {
		case SET_ini:
			flag = true;
			// Light up the LED matrix indicating the achieved score
			update_led(levels_led[score]);
			// lit_led();
			break;

		case FIRST:
			// In the first state, display the pattern or image 'A' on the LED matrix.
			update_led(A);
			break;

		case SECOND:
			// In the second state, display the pattern or image 'B'.
			update_led(B);
			break;

		case THIRD:
			// In the third state, display the pattern or image 'C'.
			update_led(C);
			break;

		case GOOD:
			// If everything is good, display a smiley face on the LED matrix.
			update_led(smileyFace);
			if (flag) {
				flag = false;
				score = score + 1;          // increase the score by one
				level_i = level_i + 1;       // increase the speed level
				level_i = level_speed_update(level_i); // increase the game speed
			}
			break;

		case BAD:
			// In case of loss, display the ghost image
			ghost_led();
			// We reset the SCORE value to 0 because the game is lost
			if (flag) {
				flag = false;
				score = SCORE_INI;          // reset the achieved score
				level_i = level_i + 1;  // increase the level to raise the speed
				level_i = level_speed_update(level_i);
			}
			break;
		default:
			/* Handle unexpected state */
			assert(0);
		}

		/* USER CODE END 3 */
	}
}
/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 72;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief ETH Initialization Function
 * @param None
 * @retval None
 */
static void MX_ETH_Init(void) {

	/* USER CODE BEGIN ETH_Init 0 */

	/* USER CODE END ETH_Init 0 */

	static uint8_t MACAddr[6];

	/* USER CODE BEGIN ETH_Init 1 */

	/* USER CODE END ETH_Init 1 */
	heth.Instance = ETH;
	MACAddr[0] = 0x00;
	MACAddr[1] = 0x80;
	MACAddr[2] = 0xE1;
	MACAddr[3] = 0x00;
	MACAddr[4] = 0x00;
	MACAddr[5] = 0x00;
	heth.Init.MACAddr = &MACAddr[0];
	heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
	heth.Init.TxDesc = DMATxDscrTab;
	heth.Init.RxDesc = DMARxDscrTab;
	heth.Init.RxBuffLen = 1524;

	/* USER CODE BEGIN MACADDRESS */

	/* USER CODE END MACADDRESS */

	if (HAL_ETH_Init(&heth) != HAL_OK) {
		Error_Handler();
	}

	memset(&TxConfig, 0, sizeof(ETH_TxPacketConfig));
	TxConfig.Attributes = ETH_TX_PACKETS_FEATURES_CSUM
			| ETH_TX_PACKETS_FEATURES_CRCPAD;
	TxConfig.ChecksumCtrl = ETH_CHECKSUM_IPHDR_PAYLOAD_INSERT_PHDR_CALC;
	TxConfig.CRCPadCtrl = ETH_CRC_PAD_INSERT;
	/* USER CODE BEGIN ETH_Init 2 */

	/* USER CODE END ETH_Init 2 */

}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void) {

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
 * @brief USB_OTG_FS Initialization Function
 * @param None
 * @retval None
 */
static void MX_USB_OTG_FS_PCD_Init(void) {

	/* USER CODE BEGIN USB_OTG_FS_Init 0 */

	/* USER CODE END USB_OTG_FS_Init 0 */

	/* USER CODE BEGIN USB_OTG_FS_Init 1 */

	/* USER CODE END USB_OTG_FS_Init 1 */
	hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
	hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
	hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
	hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
	hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
	hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
	hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
	hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
	hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
	hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
	if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USB_OTG_FS_Init 2 */

	/* USER CODE END USB_OTG_FS_Init 2 */

}

/* USER CODE BEGIN 4 */

/**
 * @brief Level Speed Update Function
 * @param position of the speed level
 * @retval returns the value of the updated speed position
 */
static int16_t level_speed_update(int16_t level_n) {
	assert(level_n >= LEVEL_MIN);
	if (level_n > LEVEL_MAX) {
		level_n = LEVEL_MIN;
	}
	speed_play = level[level_n];
	delayInit(&Delay_play, speed_play); // sets game speed

	return level_n;
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
