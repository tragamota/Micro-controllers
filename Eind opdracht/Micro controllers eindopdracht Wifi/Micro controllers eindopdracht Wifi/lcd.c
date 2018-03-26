/*
 * lcd.c
 *
 * Created: 15-3-2018 14:38:28
 *  Author: lars
 */ 
 #define F_CPU 8000000

 #include <avr/io.h>
 #include <util/delay.h>
 #include "lcd.h"

 #define RSPIN 0x04
 #define EPIN 0x08
 #define WRITE_COMMAND 4
 #define WRITE_DATA 5

 static void LCD_togglePinE(void);
 static void LCD_Command(uint8_t data);
 static void LCD_Data(uint8_t data);
 static void LCD_writeByte(uint8_t operation, uint8_t data);
 static void LCD_4bit_mode();

 void init(void) {
	 //opening for output
	 DDRC = 0xFF;
	 PORTC = 0x00;
	 
	 //Set in 4 Bit Mode
	 LCD_4bit_mode();
	 
	 //set 2 lines
	 LCD_writeByte(WRITE_COMMAND, 0x28);
	 
	 //set display ON
	 LCD_writeByte(WRITE_COMMAND, 0x0C);
	 
	 //clear display
	 LCD_writeByte(WRITE_COMMAND, 0x01);
	 
	 //go home
	 LCD_writeByte(WRITE_COMMAND, 0x02);
	 
	 //reset output
	 PORTC = 0x00;
 }

 void display_text(char *str) {
	 for(;*str; str++) {
		 LCD_writeByte(WRITE_DATA, *str);
	 }
	 PORTC = 0x00;
 }

 void set_cursor(int position) {
	 LCD_writeByte(WRITE_COMMAND, 0x02);
	 for(int i = 0; i < position; i++) {
		 LCD_writeByte(WRITE_COMMAND, 0x14);
	 }
	 PORTC = 0x00;
 }

 void shift_text(int position) {
	 for(int i = 0; i < position; i++) {
		 LCD_writeByte(WRITE_COMMAND, 0x18);
	 }
 }

 void clear_LCD() {
	 LCD_writeByte(WRITE_COMMAND, 0x01);
	 LCD_writeByte(WRITE_COMMAND, 0x02);
 }

 static void LCD_togglePinE(void) {
	 PORTC |= EPIN;
	 _delay_ms(1);
	 PORTC &= (~(EPIN));
	 _delay_ms(1);
 }

 static void LCD_Command(uint8_t data) {
	 PORTC = ((data & 0xF0));
	 LCD_togglePinE();
	 
	 PORTC = ((data & 0x0F) << 4);
	 LCD_togglePinE();
 }

 static void LCD_Data(uint8_t data) {
	 PORTC = ((data & 0xF0));
	 PORTC |= RSPIN;
	 LCD_togglePinE();
	 
	 PORTC = ((data & 0x0F) << 4);
	 PORTC |= RSPIN;
	 LCD_togglePinE();
 }

 static void LCD_writeByte(uint8_t operation, uint8_t data) {
	 if(operation == WRITE_COMMAND) {
		 LCD_Command(data);
	 }
	 else {
		 LCD_Data(data);
	 }
 }

 static void LCD_4bit_mode() {
	 PORTC = (0x02 << 4);
	 PORTD = PORTC;
	 LCD_togglePinE();
 }
