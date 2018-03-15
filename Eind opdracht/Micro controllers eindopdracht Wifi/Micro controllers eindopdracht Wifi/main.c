/*
 * Micro controllers eindopdracht Wifi.c
 *
 * Created: 14-3-2018 18:05:17
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

#include "Wifi.h"
#include "lcd.h"

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0x00;
	init();
	//display_text("LCD working");
	WifiInit();
    
    while (1) 
    {
		
    }
}

