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

int overflowCount = 0;
int tenthValue = 0;
int TimerPreset = 254;
int changed = 0;
static char text[] = "Aantal keer gedrukt: ";
int aantalKeer = 0;


int soft_prescale_counter = 0;
int pulse_pattern_counter = 0;
int pulse_pattern[] = {15, 25};

ISR(TIMER2_COMP_vect){
	if((++soft_prescale_counter) > pulse_pattern[pulse_pattern_counter]){
		PORTD ^= 1;
		pulse_pattern_counter = (pulse_pattern_counter+1)%2; // switch from software prescaler
		soft_prescale_counter = 0;
		
	}
	
}




void displayUpdate() {
	clr_display();
	display_text(text);
	lcd_writeChar(aantalKeer+'0');
}


int main(void)
{	
	DDRD = 0xff;
	PORTD = 1;											// has to begin at on when you want your bit at the port on until another interupt
	TCNT2 = 0;
	OCR2 = 0x08;
	TCCR2 = (1 << WGM21) | (1 << CS20)| (1 << CS22);	// [1] Set WGM21 to enable CTC mode, [2] Set Prescaler to 1024 a.k.a enable Bits CS20 and CS22
	TIMSK = (1 << OCIE2);								// Set interrupt mask to fire on comparator events
	sei();												// set global interupt flag
	
	while(1){
		// busy waiting
	}

	sei();
	//DDRB = 0xFF;
	//DDRC = 0xFF;
	//DDRD = 0x00;
	//
	//TCNT2 = -1;
	//TIMSK |= (1 << 6);
	//SREG |= (1 << 7);
	//TCCR2 = 0b0000111;
	//sei();
	//
	//PORTC = 0x00;
	//
	//init();
	//clr_display();
	//int length = strlen(text) + 1;
	//while (1)
	//{
	//for(int x = 0; x< length; x++) {
	//PORTB = TCNT2;
	//set_display(1);
	//wait(250);
	//}
	//}
	
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

