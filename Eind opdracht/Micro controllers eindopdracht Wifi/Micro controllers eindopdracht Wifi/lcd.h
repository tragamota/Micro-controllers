/*
 * lcd.h
 *
 * Created: 15-3-2018 14:38:54
 *  Author: larsv
 */ 


void init(void);
void display_text(char *str);
void set_cursor(int position);
void shift_text(int position);
void clear_LCD(void);