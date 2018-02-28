/*
 * Micro controllers Week 3 B1.c
 *
 * Created: 25-2-2018 19:38:03
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "lcd.h"

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0x00;
	
	DDRD = 0xFF;
	PORTD = 0x01;
	
	init();
	set_cursor(2);
	display_text("hallo Hallo");
	wait(2000);
	clear_LCD();
	display_text("We meet again luke skywalker");
	
    while (1) 
    {
		shift_text(1);
		wait(650);
    }
}

