/*
 * Micro controllers week 4 B1.c
 *
 * Created: 7-3-2018 15:35:42
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;

	ADMUX	= 0b01100000;
	ADCSRA	= 0b11100110;
	
	while (1)
	{
		PORTA = ADCH;
		PORTB = ADCL;
	}
}

