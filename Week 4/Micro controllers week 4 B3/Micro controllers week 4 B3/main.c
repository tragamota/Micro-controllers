/*
 * Micro controllers week 4 B3.c
 *
 * Created: 7-3-2018 22:11:05
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

int main(void)
{
	DDRC = 0xFF;
	init();
	
	DDRA = 0xFF;
	DDRF = 0x00;

	ADMUX	= 0b11100000;
	ADCSRA	= 0b11100110;
	
	while (1)
	{
		char tempText[16];
		int temp = ADCH;
		sprintf(tempText, "Temp  %d", temp);
		
		clear_LCD();
		display_text(tempText);
		
		wait(1500);
	}
}

