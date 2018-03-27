/*
 * Wifi.c
 *
 * Created: 14-3-2018 18:05:31
 *  Author: Ian
 */ 
#define F_CPU 8000000

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

void WifiTest(void);
void WifiWriteChar(unsigned char);
unsigned char WifiReadChar(void);

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

void WifiTest(void) {
	char ATCommand[] = "AT\r\n";
	
	int i = 0;
	while(ATCommand[i] != '\0') {
		unsigned char dataToSend = ATCommand[i];
		WifiWriteChar(dataToSend);
		i++;
	}
	wait(1000);
}

void WifiConnectToAP(char *SSID, char *password) {
	char APCommand[80];
	sprintf(APCommand, "%s\"%s\",\"%s\"\r\n", "AT+CWJAP=", SSID, password);

	int i = 0;
	while(APCommand[i] != '\0') {
		unsigned char dataToSend = APCommand[i];
		WifiWriteChar(dataToSend);
		i++;
	}
	wait(10000);
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
		i++;
	}
	
	i = 0;
	while(data[i] != '\0') {
		WifiWriteChar(data[i]);
		i++;
	}
	wait(250);
}

void WifiTcpClose() {
	char *tcpCloseCommand = "AT+CIPCLOSE\r\n";
		
	for(;*tcpCloseCommand; tcpCloseCommand++) {
		WifiWriteChar(*tcpCloseCommand);
	}
	wait(100);
}

void WifiWriteChar(unsigned char commandByte) {
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = commandByte;
}

unsigned char WifiReadChar(void) {
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}