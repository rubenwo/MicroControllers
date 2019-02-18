#define F_CPU 8000000

#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
#include "LCD.h"

void init() {
	lcd_command( 0x02 );
	lcd_command( 0x28 );
	lcd_command( 0x0C );
	lcd_command( 0x06 ); 
	lcd_command( 0x80 );
}

void display_text(char *str) {
	_delay_ms(1);
	int length = strlen(str);
	for(int x = 0; x < length; x++) {
		lcd_writeChar(str[x]);
	}
}

void set_display(int pos) {
	_delay_ms(1);
	for(int x = 0; x < pos; x++) {
		lcd_command(0b0000011000);
	}
}

void set_cursor(int pos){
	_delay_ms(1);
	clr_display();
	for(int x = 0; x < pos; x++) {
		lcd_command(0b0000010100);
	}
}

void clr_display() {
	_delay_ms(1);
	lcd_command(0x01);
}

void lcd_writeChar( unsigned char dat )
{
	PORTC = dat & 0xF0; 
	PORTC = PORTC | 0x0C;
	_delay_ms(1); 
	PORTC = 0x04; 
	PORTC = (dat & 0x0F) << 4;
	PORTC = PORTC | 0x0C;
	_delay_ms(1); 
	PORTC = 0x00;
}

void lcd_command ( unsigned char dat )
{
	PORTC = dat & 0xF0; 
	PORTC = PORTC | 0x08;
	_delay_ms(1);
	PORTC = 0x04; 
	PORTC = (dat & 0x0F) << 4; 
	PORTC = PORTC | 0x08; 
	_delay_ms(1); 
	PORTC = 0x00; 
}