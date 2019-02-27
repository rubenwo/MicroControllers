/*
* C1.c
*
* Created: 2/27/2019 11:13:10 AM
*  Author: Ruben
*/

#define F_CPU 8000000UL

#include "C1.h"
#include <avr/io.h>
#include <util/delay.h>

#define BIT(x)		( 1<<x )
#define DDR_SPI		DDRB					// spi Data direction register
#define PORT_SPI	PORTB					// spi Output register
#define SPI_SCK		1						// PB1: spi Pin System Clock
#define SPI_MOSI	2						// PB2: spi Pin MOSI
#define SPI_MISO	3						// PB3: spi Pin MISO
#define SPI_SS		0						// PB0: spi Pin Slave Select

void wait(int ms)
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

void spi_masterInit(void)
{
	DDR_SPI = 0xff;
	DDR_SPI &= ~BIT(SPI_MISO);
	PORT_SPI |= BIT(SPI_SS);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}


void spi_write( unsigned char data )
{
	SPDR = data;
	while( !(SPSR & BIT(SPIF)) );
}

char spi_writeRead( unsigned char data )
{
	SPDR = data;
	while( !(SPSR & BIT(SPIF)) );
	data = SPDR;
	return data;
}

void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

void spi_slaveDeSelect(unsigned char chipNumber)
{

	PORTB |= BIT(chipNumber);
}


void displayDriverInit()
{
	spi_slaveSelect(0);
	spi_write(0x09);
	spi_write(0xFF);
	spi_slaveDeSelect(0);

	spi_slaveSelect(0);
	spi_write(0x0A);
	spi_write(0x0F);
	spi_slaveDeSelect(0);

	spi_slaveSelect(0);
	spi_write(0x0B);
	spi_write(0x03);
	spi_slaveDeSelect(0);

	spi_slaveSelect(0);
	spi_write(0x0C);
	spi_write(0x01);
	spi_slaveDeSelect(0);
}

void displayOn()
{
	spi_slaveSelect(0);
	spi_write(0x0C);
	spi_write(0x01);
	spi_slaveDeSelect(0);
}

void displayOff()
{
	spi_slaveSelect(0);
	spi_write(0x0C);
	spi_write(0x00);
	spi_slaveDeSelect(0);
}

void spi_writeWord ( unsigned char adress, unsigned char data ) {
	spi_slaveSelect(0);
	spi_write(adress);
	spi_write(data);
	spi_slaveDeSelect(0);
}

void writeLedDisplay( int value ) {
	spi_writeWord(4, value >= 0 ? (value% 10000)/ 1000 : 10);
	value = value < 0 ? value * -1 : value;
	spi_writeWord(3, (value % 1000) / 100);
	spi_writeWord(2, (value % 100) / 10);
	spi_writeWord(1, value % 10);
}

void DoAssignmentC1(){
	DDRB=0x01;
	spi_masterInit();
	displayDriverInit();
	displayOn();
	for(int x = -999; x <= 1000; x++) {
		writeLedDisplay(x);
		wait(50);
	}
	// Opdracht b van C1 is eigenlijk onze writeLedDisplay aanroepen in week 4 opdrachten. (b3)
}
