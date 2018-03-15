/*
 * Wifi.c
 *
 * Created: 14-3-2018 18:05:31
 *  Author: Ian
 */ 
#ifndef F_CPU
	#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lcd.h"

#define BAUDRATE 9600
#define REGBAUD F_CPU/16/BAUDRATE - 1

#define BIT(__x) (1 << (__x))

static void WifiTest(void);
static void WifiWriteChar(unsigned char);
static unsigned char WifiReadChar(void);

void WifiInit(void) {
	int ubrr = REGBAUD;
	UBRR0H = ubrr>>8; // baudrate register, hoge byte
	UBRR0L = ubrr; // baudrate register, lage byte
	
	UCSR0C = 0b00000110; // asynchroon, 8 data - 1 stop - no parity
	UCSR0B = 0b00000000; // receiver & transmitter disable
	UCSR0B |= BIT(RXEN)|BIT(TXEN);

	WifiTest();
}

static void WifiTest(void) {
	char *ATCommand = "AT\r\n";
	
	for(;*ATCommand; ATCommand++) {
		WifiWriteChar(*ATCommand);
	}

	clear_LCD();
	display_text("Send command");
	char receiveBuffer[5]; 
	clear_LCD();
	char buffer[5];
	memset(buffer, 0, sizeof(buffer));
	
	for(int i = 0; i < 4; i++) {
 		char textToDisplay[16];
 		sprintf(textToDisplay, "Reading byte %d", i);
 		display_text(textToDisplay);
 		char receivedByte = WifiReadChar();
 		//strcat(receiveBuffer, &receivedByte);
		buffer[i] = receivedByte;
	}

	clear_LCD();
	display_text(buffer);
	_delay_ms(500);

	if(!strcmp(receiveBuffer, "OK\r\n")) {
		//clear_LCD();
		//display_text("WiFi Working!");
	}
	else {
		//clear_LCD();
		//display_text("WiFi not Working!");
	}
	for(;;);
}

void WifiRequestAP(char **AP) {
	
}

static void WifiWriteChar(unsigned char commandByte) {
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = commandByte;
}

static unsigned char WifiReadChar(void) {
	while(!(UCSR0A & (1<<RXC)));
	return UDR0;
}