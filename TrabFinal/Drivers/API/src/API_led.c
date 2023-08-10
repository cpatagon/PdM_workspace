/*
 * API_led.c
 *
 *  Created on: Aug 6, 2023
 *      Author: lgomez
 */
//#include "API_led.h"
#include <stdint.h>
#include "API_spi.h"

uint8_t led_address[] = {0x01,0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
uint8_t clear[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t matrizEncendida[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};


typedef enum{
	SET_ini,
	A,
	B,
	C,
	GOOD,
	BAD,
} def_Led_t;


void clear_led(void){
	for(int j = 0; j < 8; j++) {
		spi_write(led_address[j],clear[j] );
	}
}

void init_led(void){
	spi_write(0x09, 0x00);       //  no decoding
	spi_write(0x0b, 0x07);       //  scan limit = 8 LEDs
	spi_write(0x0c, 0x01);       //  power down =0,normal mode = 1
	spi_write(0x0f, 0x00);       //  no test display
	clear_led();
	spi_write(0x0a, 0x05);       //  brightness intensity
};

void lit_led(void){
	for(int j = 0; j < 8; j++) {
		spi_write(led_address[j], matrizEncendida[j]);
	}
};

/* se dibuja una lista de caracteres binarios en forma decimal
 * dondde cada valor escrito en exadeciamal representa una fila de la matriz
 * led_adress son el nombre de cada comluna escrito en exadecimal*/
void update_led(uint8_t  paint_list[]){
	 for(int j = 0; j < 8; j++) {
			 spi_write(led_address[j], paint_list[j]);
		 }
};
