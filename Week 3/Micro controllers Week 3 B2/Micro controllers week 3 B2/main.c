/*
 * Micro controllers week 3 B2.c
 *
 * Created: 1-3-2018 16:04:01
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	init();

	DDRD = 0x00;
	PORTD = 0x00;

	TCCR2 = 0x07;
	TCNT2 = 0x00;

    while (1) 
    {
    }
}

