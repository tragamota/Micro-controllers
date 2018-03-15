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

#include <string.h>
#include <stdlib.h>

#include "lcd.h"

#define BAUDRATE 9600
#define REGBAUD F_CPU/16/BAUDRATE - 1

static void WifiTest(void);
static void WifiWriteChar(unsigned char);
static unsigned char WifiReadChar(void);

void WifiInit(void) {
	int baud = REGBAUD;
	UBRR0H = (baud>>8);		//highest 4 bits of the baudrate
	UBRR0L = baud;			//lowest byte of the baudrate
		
	UCSR0B = 0x0C;			//enable TX en RX
	UCSR0C = 0x06;			//asychroon 8bits en no parity ingesteld.
	clear_LCD();
	display_text("Baudinit");
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
	
	for(int i = 0; i < (sizeof(receiveBuffer) / sizeof(char)) - 1; i++) {
		char receivedByte = WifiReadChar();
		clear_LCD();
		display_text("  Byte: " + receivedByte);
		strcat(receiveBuffer, &receivedByte);
	}
	
	if(!strcmp(receiveBuffer, "OK")) {
		display_text("WiFi Working!");
	}
	else {
		display_text("WiFi not Working!");
	}
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