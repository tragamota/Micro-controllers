/*
 * lcd.h
 *
 * Created: 25-2-2018 19:57:01
 *  Author: Ian
 */ 

void init(void);
void display_text(char *str);
void set_cursor(int position);
void shift_text(int position);
void clear_LCD(void);