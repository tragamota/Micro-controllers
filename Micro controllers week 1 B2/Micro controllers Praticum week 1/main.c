/*
 * Micro controllers Praticum week 1.c
 *
 * Created: 3-2-2018 14:43:03
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0B11000000;
    /* Replace with your application code */
    while (1) 
    {
		PORTD = 0b10000000;
		wait(500);
		PORTD = 0b01000000;
		wait(500);
    }
}

