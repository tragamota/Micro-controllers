/*
 * Micro controllers week 3 B3.c
 *
 * Created: 7-3-2018 13:58:23
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int msCounter = 0;

ISR(TIMER2_COMP_vect) {
	msCounter++;
	msCounter %= 40;
	if(msCounter  < 15) {
		PORTD = 0x00;
	}
	else {
		PORTD = 0x80;
	}
}

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	OCR2 = 125;
	TIMSK |= (1 << 7);
	TCCR2 = 0b0001011;
	
	sei();
	
    while (1) 
    {
    }
}