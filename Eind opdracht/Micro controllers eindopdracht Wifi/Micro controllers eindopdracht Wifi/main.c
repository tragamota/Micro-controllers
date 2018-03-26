/*
 * Micro controllers eindopdracht Wifi.c
 *
 * Created: 14-3-2018 18:05:17
 * Author : Ian
 */ 
#define F_CPU 8000000

#include <stdio.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "Wifi.h"
#include "lcd.h"

#define LIGHT_ON 1
#define LIGHT_OFF 0
#define LIGHT_NO_ACTION 2

#define HUE_USER_KEY "null"
#define HUE_IP "192.168.0.23"
#define HUE_PORT 80
#define HUE_GROUP_URL "/api/"HUE_USER_KEY"/groups/0/action"

char userLightAction = LIGHT_NO_ACTION;
static char HUE_GROUP_ON_JSON[]		= "{ \"on\": true }";
static char HUE_GROUP_OFF_JSON[]	= "{ \"on\": false }";
	
ISR(INT0_vect) {
	userLightAction = LIGHT_ON;
}

ISR(INT1_vect) {
	userLightAction = LIGHT_OFF;
}

void enableInterrupt() {
	//setting external interrupt pins as input with pull up.
	DDRD	= 0x00;
	PORTD	= 0x03;
	
	//interrupts are rising edge and activated
	EICRA = 0x0F;
	EIMSK = 0x03;
	sei();
}

void combineHeaderWithData(char *data, char *des, int size) {
	char headerWithData[256];
	sprintf(headerWithData, "%s%s%s%s%s%s%s%s%s%s%d%s%s", 
	"PUT ", HUE_GROUP_URL, " HTTP/1.1\r\n", 
	"USER_AGENT: AVR-ESP826\r\n", 
	"Content-Type: application/json\r\n",
	"Host: ", HUE_IP, 
	"\r\nConnection: Keep-Alive\r\n",
	"Accept-Encoding: gzip\r\n",
	"Content-Length: ", size, "\r\n\r\n", data);
	des = strcpy(des, headerWithData);
}


int main(void) {
	init();
	//WifiInit();
	enableInterrupt();
	
	char headerWithData[256];
	combineHeaderWithData(HUE_GROUP_ON_JSON, headerWithData, strlen(HUE_GROUP_ON_JSON));
	char userLightAction_shadowCopy;
    while (1) 
    {
		ATOMIC_BLOCK(ATOMIC_FORCEON) {
			userLightAction_shadowCopy = userLightAction;
			userLightAction = LIGHT_NO_ACTION;
		}
		
		if(userLightAction_shadowCopy != LIGHT_NO_ACTION) {
			WifiTcpConnect(HUE_IP, HUE_PORT);
			if(userLightAction_shadowCopy == LIGHT_ON) {
				combineHeaderWithData(HUE_GROUP_ON_JSON, headerWithData, strlen(HUE_GROUP_ON_JSON));
				WifiTcpSendData(headerWithData, strlen(headerWithData));
			}
			else {
				combineHeaderWithData(HUE_GROUP_OFF_JSON, headerWithData, strlen(HUE_GROUP_OFF_JSON));
				WifiTcpSendData(headerWithData, strlen(headerWithData));
			}
			WifiTcpClose();
		}
		//go in sleep
		sleep_mode();
    }
}

