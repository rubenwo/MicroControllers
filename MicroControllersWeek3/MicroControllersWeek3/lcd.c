/*
* lcd.c
*
* Created: 2/13/2019 10:48:19 AM
*  Author: diabl
*/
#define F_CPU 8000000UL

#include "lcd.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);

void init(){
	DDRC = 0xFF;
	PORTC = 0x00;
	
	PORTC = 0x20;
	lcd_strobe_lcd_e();

	PORTC = 0x20;
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
}

void display_text(char *str){
	for(;*str; str++){
		_delay_ms(1);
		lcd_write_data(*str);
	}
}
void set_cursor(int position){
	
}

void lcd_write_data(unsigned char byte)
{
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}
void lcd_write_command(unsigned char byte)
{
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}
void lcd_strobe_lcd_e(void)

{
	PORTC |= (1<<LCD_E);
	_delay_ms(1);
	PORTC &= ~(1<<LCD_E);
	_delay_ms(1);
}

void clear(void){
	// Implement clearing
}
