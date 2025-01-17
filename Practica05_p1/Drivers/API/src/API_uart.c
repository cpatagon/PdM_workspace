#include <stdint.h>  /* For standard uint32_t types */
#include <stdbool.h> /* For standard boolean types */
#include "API_uart.h"

#include "stm32f4xx_hal.h"          /* HAL library inclusion */
#include "stm32f4xx_nucleo_144.h"   /* BSP library inclusion */

typedef bool bool_t;

/* UART handler declaration */
static UART_HandleTypeDef UartHandle;

//static void Error_Handler(void);

#define USARTx  USART3
#define RATE	9600

//extern UART_HandleTypeDef huart1;

/* mensaje con los parametros de configuracion de la UART */
static const char *message =
	"\n\n"
	"-----------------------------------------------------------\n"
	"*** UART port initialization successful !!! ***\n"
	"-----------------------------------------------------------\n"
	"\n"
    "  UART configured as follows:\n"
    "      - Word Length = 8 Bits (7 data bit + 1 parity bit) :\n"
    "                      BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal\n"
    "      - Stop Bit    = One Stop bit\n"
    "      - Parity      = ODD parity\n"
    "      - BaudRate    = 9600 baud\n"
    "      - Hardware flow control disabled (RTS and CTS signals)\n";

/* funcion de inicialización de la UART. Adicionalmente, debe imprimime
 * por la terminal serie un mensaje con los parámetros de
 * configuración*/

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

	  UartHandle.Init.BaudRate   = RATE;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	  	if (HAL_UART_Init(&UartHandle) == HAL_OK) {
	  		uartSendString(message); // envia mensaje con los parametros de configuración UART
	  		return true;
	  	} else {
	  		return false;
	  	}
	  }

/* uartSendString(uint8_t *pstring) recibe un puntero a un
 * string que se desea enviar por la UART completo (hasta
 * el caracter ‘\0’) y debe utilizar la función de la
 * HAL HAL_UART_Transmit(...) para transmitir el string.*/

void uartSendString(uint8_t * pstring){
    HAL_UART_Transmit(&UartHandle, pstring, strlen((char *)pstring), HAL_MAX_DELAY);
}

/* uartSendStringSize(uint8_t * pstring, uint16_t size)
 * recibe un puntero a un string que se desea enviar por
 * la UART y un entero con la cantidad de caracteres que
 * debe enviar. La función debe utilizar
 * HAL_UART_Transmit(...) para transmitir el string.
 * */

void uartSendStringSize(uint8_t * pstring, uint16_t size){
    HAL_UART_Transmit(&UartHandle, pstring, size, HAL_MAX_DELAY);
}

/* uartReceiveStringSize(uint8_t * pstring, uint16_t size)
 * recibe un puntero a un string que se desea enviar por
 * la UART y un entero con la cantidad de caracteres que
 * debe enviar. La función debe utilizar
 * HAL_UART_Transmit(...) para transmitir el string.
 * */

void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
    HAL_UART_Receive(&UartHandle, pstring, size, HAL_MAX_DELAY);
}
