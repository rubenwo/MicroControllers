/*
* b1.c
*
* Created: 2/20/2019 11:21:00 AM
*  Author: Ruben
*/


#define F_CPU 8000000
#define BIT(x)	(1 << (x))



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "b1.h"


static void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}

// Initialize ADC: 10-bits (left justified), free running
static void adcInit( void )
{
	ADMUX = 0b01100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}


void DoB1(){
	DDRF = 0x00;
	DDRA = 0xFF;
	DDRB = 0xFF;
	
	adcInit();
	
	while(1){
		PORTB = ADCL;
		PORTA = ADCH;
		wait(100);
	}
}