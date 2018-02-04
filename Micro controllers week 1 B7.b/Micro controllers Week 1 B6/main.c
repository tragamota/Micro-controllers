/*
 * Micro controllers Week 1 B6.c
 *
 * Created: 3-2-2018 18:09:45
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

const short totalLeds = 6;

typedef struct LEDINFO {
	unsigned char portIO;
	unsigned char portState;
} LEDINFO;


const LEDINFO states[] = {
	{0x03, 0x01}, {0x03, 0x02}, {0x06, 0x02}, {0x06, 0x04}, {0x05, 0x01}, {0x05, 0x04}
};

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void setCharliePlexingLed(int nr) {
	DDRC = states[nr].portIO;
	PORTC = states[nr].portState;
	wait(350);
}

int main(void)
{
	short index = 0;
    while (1) 
    {
		index = 0;
		while(index < totalLeds) {
			setCharliePlexingLed(index);
			index++;
		}
		PORTC = 0x00;
		wait(1000);
    }
}

