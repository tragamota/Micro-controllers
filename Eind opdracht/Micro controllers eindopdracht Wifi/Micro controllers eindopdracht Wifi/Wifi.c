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
#include "Wifi.h"

#define BAUDRATE 9600
#define REGBAUD F_CPU/16/BAUDRATE - 1

static void WifiTest(void);
static void WifiWriteChar(unsigned char);
static unsigned char WifiReadChar(void);

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void WifiInit(void) {
	int baud = REGBAUD;
	UBRR0H = (baud>>8);		//highest 4 bits of the baudrate
	UBRR0L = baud;			//lowest byte of the baudrate

	UCSR0C = 0x06;			//asychroon 8bits en no parity ingesteld.
	UCSR0B = 0x0C;			//enable TX en RX
	UCSR0A = 0x00;
	
	WifiTest();
}

static void WifiTest(void) {
	char *ATCommand = "AT\r\n";
	
	for(;*ATCommand; ATCommand++) {
		WifiWriteChar(*ATCommand);
	}

	char receiveBuffer[5]; 
	
	for(int i = 0; i < 4; i++) {
 		char receivedByte = WifiReadChar();
 		strcat(receiveBuffer, &receivedByte);
	}

	clear_LCD();
	if(strstr(receiveBuffer, "OK") != NULL) {
		display_text("Wifi Is OK");
	}
	if(!strcmp(receiveBuffer, "OK\r\n")) {
		display_text("WiFi Working!");
	}
	else {
		display_text("WiFi not Working!");
	}
}

void WifiTcpConnect(char *IP, int port) {
	char tcpStartCommand[50];
	sprintf(tcpStartCommand, "%s,%s,%d\r\n", "AT+CIPSTART=\"TCP\"", IP, port);
	
	int i = 0;
	while(tcpStartCommand[i] != '\0') {
		WifiWriteChar(tcpStartCommand[i]);
	}
	wait(250);
}

void WifiTcpSendData(char *data, int size) {
	int i = 0;
	char tcpSendDataCommand[18];
	
	sprintf(tcpSendDataCommand, "%s%d\r\n", "AT+CIPSEND=", size);
	
	
	while(tcpSendDataCommand[i] != '\0') {
		WifiWriteChar(tcpSendDataCommand[i]);
	}
	
	i = 0;
	while(data[i] != '\0') {
		WifiWriteChar(data[i]);
	}
	wait(500);
}

void WifiTcpClose() {
	char *tcpCloseCommand = "AT+CIPCLOSE\r\n";
		
	for(;*tcpCloseCommand; tcpCloseCommand++) {
		WifiWriteChar(*tcpCloseCommand);
	}
	wait(100);
}

static void WifiWriteChar(unsigned char commandByte) {
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = commandByte;
}

static unsigned char WifiReadChar(void) {
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}