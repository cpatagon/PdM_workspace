/*
 * API_led.h
 *
 *  Created on: Aug 6, 2023
 *      Author: lgomez
 */

#ifndef API_INC_API_LED_H_
#define API_INC_API_LED_H_

uint8_t led_ocho[]    = {0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x3C};
uint8_t smileyFace[]  = {0x00, 0x66, 0x66, 0x18, 0x00, 0x42, 0x3C, 0x00};
uint8_t badFace[]     = {0x00, 0x66, 0x66, 0x00, 0x18, 0x42, 0x3C, 0x00};  // Cara Triste
uint8_t A[]           = {0x00, 0x3C, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00};  // Letra A
uint8_t B[]           = {0x00, 0x7C, 0x42, 0x7C, 0x7C, 0x42, 0x7C, 0x00};  // Letra B
uint8_t C[]           = {0x00, 0x3C, 0x42, 0x40, 0x40, 0x42, 0x3C, 0x00};  // Letra C
uint8_t reloj[]       = {0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18};  // Reloj Analógico
uint8_t ghost1[] = {0x18,0x7e,0xff,0xbd,0xff,0xff,0xff,0xa5};
uint8_t ghost2[] = {0x18,0x7e,0xbd,0xff,0xff,0xff,0xff,0xa5};
uint8_t ghost3[] = {0x18,0x7e,0xdb,0xff,0xff,0xff,0xff,0xa5};
uint8_t ghost4[] = {0x18,0x7e,0xff,0xdb,0xff,0xff,0xff,0xa5};
uint8_t ghost5[] = {0x18,0x7e,0x99,0x99,0xff,0xff,0xff,0xa5};
uint8_t ghost6[] = {0x3c,0x7e,0xd7,0xff,0xc3,0xff,0xff,0xdb};

void clear_led(void);
void init_led(void);
void lit_led(void);


void update_led(uint8_t paint_list[]);

#endif /* API_INC_API_LED_H_ */
