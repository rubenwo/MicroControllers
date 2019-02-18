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
static char text[] = "Aantal keer gedrukt: ";
int aantalKeer = 0;


ISR ( TIMER2_OVF_vect ) {
	aantalKeer++;
	displayUpdate();
	TCNT2 = -1;
}

void displayUpdate() {
	clr_display();
	display_text(text);
	lcd_writeChar(aantalKeer+'0');
}


int main(void)
{
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0x00;
	
	TCNT2 = -1;
	TIMSK |= (1 << 6);
	SREG |= (1 << 7);
	TCCR2 = 0b0000111;
	sei();
	
	PORTC = 0x00;
	
	init();
	clr_display();
	int length = strlen(text) + 1;
	while (1)
	{
		for(int x = 0; x< length; x++) {
			PORTB = TCNT2;
			set_display(1);
			wait(250);
		}
	}
	
	return 0;
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

