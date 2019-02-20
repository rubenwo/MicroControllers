/*
* b2.c
*
* Created: 2/20/2019 11:23:42 AM
*  Author: Ruben
*/

#define F_CPU 8000000
#define BIT(x)	(1 << (x))


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "b2.h"


static void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}

static void adcInit( void )
{
	ADMUX = 0b01100011;			// AREF=VCC, result left adjusted, channel3 at pin PF3
	ADCSRA = 0b10000110;		// ADC-enable, no interrupt, no free running, division by 64
}


void DoB2(){
	DDRF = 0x00;
	DDRA = 0xFF;
	adcInit();

	while (1)
	{
		ADCSRA |= BIT(6);
		while ( ADCSRA & BIT(6) ) ;
		PORTA = ADCH;
		wait(500);
	}
}
