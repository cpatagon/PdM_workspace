#include <stdint.h>  /* For standard uint32_t types */
#include <stdbool.h> /* For standard boolean types */
#include "API_uart.h"

#include "stm32f4xx_hal.h"          /* HAL library inclusion */
#include "stm32f4xx_nucleo_144.h"   /* BSP library inclusion */

typedef bool bool_t;

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

//static void Error_Handler(void);

#define USARTx                           USART3

extern UART_HandleTypeDef huart1;

bool_t uartInit(){
	 /*##-1- Configure the UART peripheral ######################################*/
	  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	  /* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	  printf("UART configurado con baud rate: %ld\n", (long)UartHandle.Init.BaudRate);

	  	if (HAL_UART_Init(&UartHandle) == HAL_OK) {
	  		return true;
	  	} else {
	  		return false;
	  	}
	  }

void uartSendString(uint8_t * pstring){
    HAL_UART_Transmit(&UartHandle, pstring, strlen((char *)pstring), HAL_MAX_DELAY);
}

void uartSendStringSize(uint8_t * pstring, uint16_t size){
    HAL_UART_Transmit(&UartHandle, pstring, size, HAL_MAX_DELAY);
}
void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
    HAL_UART_Receive(&UartHandle, pstring, size, HAL_MAX_DELAY);
}

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}