/*
 * Micro controllers week 1, B3.c
 *
 * Created: 3-2-2018 15:07:01
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
	DDRD = 0b10000000;
	DDRC = 0b00000000;
    /* Replace with your application code */
    while (1) 
    {
		if((PINC & 0b00000001) == 1) {
			PORTD = 0b10000000;
			wait(250);
			PORTD = 0x00;
			wait(250);
		}
    }
}

