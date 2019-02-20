/*
* b3.c
*
* Created: 2/20/2019 11:40:00 AM
*  Author: Ruben
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "b3.h"
#define BIT(x)	(1 << (x))




static void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );
	}
}




void DoB3(){
	
}