/*
 * Micro controllers week 2 B2.c
 *
 * Created: 13-2-2018 18:48:52
 * Author : Ian
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>


ISR(INT1_vect) {
	PORTC <<= 1;
	if(PORTC <= 0x00) {
		PORTC = 0x01;
	}
}

ISR(INT2_vect) {
	PORTC >>= 1;
	if(PORTC <= 0x00) {
		PORTC = 0x80;
	}
}


int main(void)
{
	/* set PIN(0-3) input & PIN(4-7) output */
	DDRD  = 0b11110000;
	PORTD = 0b00001111;
	
	/* set all PINS on PORTC to output */
	DDRC = 0xFF;
	PORTC = 0x01;
	
	//enable interrupt
	EICRA |= 0b00111100;
	EIMSK |= 0x06;
	
	sei();
    while (1) 
    {
		/* enter low energy mode A.K.A sleep */
		sleep_mode();
    }
}

