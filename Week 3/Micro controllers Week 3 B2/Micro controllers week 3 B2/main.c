/*
 * Micro controllers week 3 B2.c
 *
 * Created: 1-3-2018 16:04:01
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <stdio.h>
#include <stdlib.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "lcd.h"

void wait(short ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

int main(void)
{
	init();
	
	DDRA = 0xFF;
	PORTA = 0x00;
	
	DDRD = 0x00;
	PORTD = 0x00;

	TCNT2 = 0x01;
	TCCR2 = 0x07;

	uint8_t counterCopyValue = 0;
	display_text("0");
    while (1) 
    {
		if(counterCopyValue != TCNT2) {
			counterCopyValue = TCNT2;
			char numberInText[4];
			sprintf(numberInText, "%d", counterCopyValue);
			
			clear_LCD();
			display_text(numberInText);
		}
    }
}

