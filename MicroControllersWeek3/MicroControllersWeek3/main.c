/*
* MicroControllersWeek3.c
*
* Created: 2/13/2019 10:36:07 AM
* Author :
*/
#define F_CPU 8000000UL
#define BIT(x) (1<<x)
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

void wait(int millis)
{
	for(int i = 0; i < millis; i++)
	{
		_delay_ms(1);
	}
}


int tenthValue = 0;
int TimerPreset = 254;
int changed = 0;


ISR(TIMER2_COMP_vect)
{
	TCNT2 = TimerPreset;
	tenthValue++;
	changed++;
}

void timer2Init( void )
{
	TCNT2 = TimerPreset; // Preset value of counter 2
	TIMSK |= BIT(6); // T2 overflow interrupt enable

	SREG |= BIT(7);

	TCCR2 = 0x07; // Initialize T2: ext.counting, rising edge, run
}

int main(void)
{
	DDRD &= ~BIT(7);
	DDRA = 0xFF;
	DDRB = 0xFF;

	//DDRD = 0xFF;
	init();
	timer2Init();
	sei();

	//opdr. B1
	//display_text("Hello world!");
	int t = 0;
	while (1)
	{
		PORTA = TCNT2; // show value counter 2
		PORTB = tenthValue; // show value tenth counter
		if(t == 50){
			t = 0;
			changed = 1;
		}
		t++;
		if(changed != 0){
			char str[10];
			sprintf(str, "%d", tenthValue);
			//uint8_t data = tenthValue + 48;
			display_text("FUCK YOU");

			changed = 0;
		}
		wait(100);
	}
}

/*
int msCount = 0;
int seconden = 0;
int minuten=0;
int uren = 0;
ISR( TIMER2_COMP_vect )
{
msCount++; // Increment ms counter
if ( msCount == 1000 )
{
PORTC ^= BIT(0); // Toggle bit 0 van PORTC
msCount = 0; // Reset ms_count value
seconden++;
if ( seconden ==60 )
{
seconden = 0;
minuten++;
if (minuten == 60 )
{
minuten = 0;
uren++;
}


}
}
}
int TimerPreset =2;
void timer2Init( void )
{
TCNT2 = TimerPreset; // Preset value of counter 2
TIMSK |= BIT(6); // T2 overflow interrupt enable

SREG |= BIT(7);
sei();

TCCR2 = 0x07; // Initialize T2: ext.counting, rising edge, run
}
int main(void){
DDRC = 0xFF; // set PORTC for output (toggle PC0)
timer2Init();
while (1)
{
// do something else
wait(10); // every 10 ms (busy waiting
}
}*/

