/*
*  main.c
*
*  Created: 1/30/2019 12:26:15 PM
*  Author: Ruben, Bart en Olaf
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void wait(int ms);
/* OPDRACHT: B.2
int main(void){
DDRD = 0b11111111;

while(1){
PORTD = 0b1000000;
wait(250);
PORTD = 0b0100000;
wait(250);
}
return 1;
}*/

/* OPDRACHT B.3
int main(void){

// set PORTD for output
DDRD = 0b11111111;
PORTC = 0x10;

while (1)
{
if (PINC & 0b00000001)
{
PORTD = 0b10000000;
wait(50);
PORTD = 0b00000000;
}
else
{
PORTD = 0x00;
}
}

return 1;
}*/


/* OPDRACHT B.4
int main(void){
DDRD = 0b11111111;
PORTD = 0b00000001;
int down = 0;

while(1){
if(down == 0){
PORTD = PORTD<< 1;
}else{
PORTD = PORTD >> 1;
}
if(PORTD & 0x80){
down = 1;
}if(PORTD & 0x01){
down = 0;
}
wait(100);
}
return 1;
}*/

/* OPDRACHT B.5*/
typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x00, 100},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};


int main(void){
	DDRD = 0b11111111;
	
	while (1==1)
	{
		int index = 0;
		while( pattern[index].delay != 0 ) {
			PORTD = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	}

	return 1;
}


void wait(int ms){
	for(int i = 0; i< ms; i++){
		_delay_ms(1);
	}
}
