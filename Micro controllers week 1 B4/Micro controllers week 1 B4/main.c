/*
 * Micro controllers week 1 B4.c
 *
 * Created: 3-2-2018 15:30:44
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
    /* Replace with your application code */
	DDRD = 0xFF;
    while (1) 
    {
		PORTD = 0x01;
		while(PORTD != 0) {
			wait(50);
			PORTD <<= 1;
		}
    }
}

