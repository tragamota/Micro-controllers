/*
 * Micro controllers week 2 B3.c
 *
 * Created: 14-2-2018 14:05:08
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <util/atomic.h>

volatile int8_t digit = 0;
volatile int8_t int0, int1;

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

ISR(INT0_vect) {
	int0 = 1;
	digit++;
}

ISR(INT1_vect) {
	int1 = 1;
	digit--;
}

void display(int8_t digit) {
	if(digit < 0 || digit > 15) {
		PORTC = 0b01111001;
	}
	else {
		PORTC = digit;
	}
}

int main(void)
{
	int8_t counterCopy;
	DDRC = 0xFF;
	PORTC = 0x07;
	
	DDRD = 0x00;
	PORTD = 0x00;
	
	EICRA = 0x0F;
	EIMSK = 0x03;
	
	sei();
    while (1) 
    {
		wait(200);
		ATOMIC_BLOCK(ATOMIC_FORCEON) {
			counterCopy = digit;
		}
		if(int0 && int1) {
			digit = 0;
			counterCopy = 0;
			int0 = 0;
			int1 = 0;
		}
		else {
			int0 = 0;
			int1 = 0;
		}
		
		display(counterCopy);
		sleep_mode();
    }
}

