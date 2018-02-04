/*
 * Micro controllers week 1 B5.c
 *
 * Created: 3-2-2018 15:55:45
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	unsigned char data;
	unsigned short waitTime; 
	unsigned char lastOperation;
} PATERN_INSTRUCTION_STRUCT;

PATERN_INSTRUCTION_STRUCT pattern[] = {
	{0x00, 500, 0}, {0x18, 150, 0}, {0x24, 150, 0}, {0x42, 150, 0}, {0x81, 150, 0}, {0x00, 150, 0},	//start from middle go to outside pattern
	{0x01, 250, 0}, {0x80, 250, 0}, {0x02, 250, 0}, {0x40, 250, 0}, {0x04, 250, 0}, {0x20, 250, 0}, {0x08, 250, 0}, {0x10, 250, 0}, {0,0,1}
};

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
		int index = 0;
		while(pattern[index].lastOperation == 0) {
			PORTD = pattern[index].data;
			wait(pattern[index].waitTime);
			index++;
		}
		PORTD = 0;
    }
}

