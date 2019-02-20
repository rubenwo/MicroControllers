/*
* b3.c
*
* Created: 2/20/2019 11:40:00 AM
*  Author: Ruben
*/

#define F_CPU 8000000
#define BIT(x)	(1 << (x))


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


#include "lcd.h"
#include "b3.h"


static void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}




void DoB3(){
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x00;
	DDRF = 0x00;
	
	ADMUX = 0b11100000;
	ADCSRA = 0b11100110;
	
	init();
	wait(100);
	
	while (1)
	{
		clr_display();
		char string[16];
		int temp = ADCH;
		sprintf(string, "Temp: %.2d", temp);
		display_text(string);
		PORTA = ADCH;
		wait(1000);
	}
}