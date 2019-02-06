/*
* MicroControllersWeek2.c
*
* Created: 2/6/2019 10:18:41 AM
* Author : Ruben Woldhuis
*/

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** ioisr.c
**
** Beschrijving:	ISR on PORTD demonstrattion
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c ioisr.c
**					avr-gcc -g -mmcu=atmega128 -o ioisr.elf ioisr.o
**					avr-objcopy -O ihex ioisr.elf ioisr.hex
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/
#define F_CPU  8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const unsigned char nums[] = {
	0b00111111, // 0
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
};

volatile int definedBit = 0;
void display(int digit);
/******************************************************************/
void wait( int ms )
/*
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:
notes:			Busy wait, not very accurate. Make sure (external)
clock value is set. This is used by _delay_ms inside
util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
ISR( INT0_vect )
/*
short:			ISR INT0
inputs:
outputs:
notes:			Set PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	if(definedBit < 7)
	definedBit++;
	PORTA = (1<<definedBit);
}

/******************************************************************/
ISR( INT1_vect )
/*
short:			ISR INT1
inputs:
outputs:
notes:			Clear PORTD.5
Version :    	DMK, Initial code
*******************************************************************/
{
	if(definedBit > -1)
	definedBit--;
	PORTA = (1<<definedBit);
}

/******************************************************************/
int main( void )
/*
short:			main() loop, entry point of executable
inputs:
outputs:
notes:			Slow background task after init ISR
Version :    	DMK, Initial code
*******************************************************************/
{
	// Init I/O
	DDRA = 0xFF;			// PORTD(7:4) output, PORTD(3:0) input, 1110 0000
	PORTA = 0x01;
	DDRD = 0xF0;

	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge, 0000 1011
	EIMSK |= 0x03;			// Enable INT1 & INT0, 0000 0011
	
	// Enable global interrupt system
	// SREG = 0x80;			// Of direct via SREG of via wrapper, 1000 0000
	sei();

	while (1)
	{
	}

	return 1;
}

void display(int digit){
	
}

