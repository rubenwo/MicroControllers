/*
* MicroControllersWeek3.c
*
* Created: 2/13/2019 10:36:07 AM
* Author :
*/
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
	
	init();
	display_text("Hello world");
	/* Replace with your application code */
	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		_delay_ms( 250 );
	}
}

