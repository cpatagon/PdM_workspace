#ifndef __API_UART_H__
#define __API_UART_H__

#include <stdint.h>  /* For standard uint32_t types */
#include <stdbool.h> /* For standard boolean types */
#include <stdio.h>

#include "stm32f4xx_hal.h"          /* HAL library inclusion */
#include "stm32f4xx_nucleo_144.h"   /* BSP library inclusion */


typedef bool bool_t;

//extern UART_HandleTypeDef UartHandle;

/* funcion de inicialización de la UART. Adicionalmente, debe imprimime
 * por la terminal serie un mensaje con los parámetros de
 * configuración*/

bool_t uartInit();

/* uartSendString(uint8_t *pstring) recibe un puntero a un
 * string que se desea enviar por la UART completo (hasta
 * el caracter ‘\0’) y debe utilizar la función de la
 * HAL HAL_UART_Transmit(...) para transmitir el string.*/

void uartSendString(char * pstring);

/* uartSendStringSize(uint8_t * pstring, uint16_t size)
 * recibe un puntero a un string que se desea enviar por
 * la UART y un entero con la cantidad de caracteres que
 * debe enviar. La función debe utilizar
 * HAL_UART_Transmit(...) para transmitir el string.
 * */

void uartSendStringSize(uint8_t * pstring, uint16_t size);

/* uartReceiveStringSize(uint8_t * pstring, uint16_t size)
 * recibe un puntero a un string que se desea enviar por
 * la UART y un entero con la cantidad de caracteres que
 * debe enviar. La función debe utilizar
 * HAL_UART_Transmit(...) para transmitir el string.
 * */

void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3


#endif // __API_UART_H__
