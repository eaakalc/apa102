/* 
* LEDStrip.cpp
*
* Created: 02/11/2020 09.54.40
* Author: Kaare
*/
#include "LEDStrip.h"
#define F_CPU 16000000UL

int size = 0;
LED *leds;
uint8_t useSPI = 0;
uint8_t brightness;

LEDStrip::LEDStrip(uint8_t rows, uint8_t columns, uint8_t br, uint8_t comms)
{
	if(br < 32)
		brightness = br;
	else
		brightness = 31;
	
	if(comms)
	{
		useSPI = 1;
		
		DDRB |= (1 << 2) | (1 << 3) | (1 << 5);

		// enable SPI, set as master, and clock to fosc/128
		SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0);
	}
	else
	{
		DDRB |= (1 << 3) | (1 << 5);
	}
	
	leds = new LED[rows * columns];
	
	for (int i = 0; i < rows * columns; i++)
	{
		setLED(i, 0, 0, 0);
	}
}

LEDStrip::~LEDStrip()
{
	delete[] leds;
}

void setLED(uint8_t pos, uint8_t r, uint8_t g, uint8_t b)
{
	leds[pos]._r = r;
	leds[pos]._g = g;
	leds[pos]._b = b;
}

void clearLED(uint8_t pos)
{
	leds[pos]._r = 0;
	leds[pos]._g = 0;
	leds[pos]._b = 0;
}

void sendByte(uint8_t byte)
{
	uint8_t data = byte;
	
	if(useSPI)
	{
		SPDR = data;
	
		while(!(SPSR & (1 << SPIF)));
	}
	else
	{
		if(data & 128)
			PORTB |= (1 << 3);
		else
			PORTB &= ~(1 << 3);
			
		data <<= 1;
		
		PORTB |= (1 << 5);
		_delay_ms(1);
		PORTB &= ~(1 << 5);
	}
}

void sendFrames()
{
	sendByte(0);
	
	for (uint8_t i = 0; i < (sizeof(leds) / sizeof(LED)); i++)
	{
		sendByte(224 + brightness);
		sendByte(leds[i]._b);
		sendByte(leds[i]._g);
		sendByte(leds[i]._r);
	}
	
	sendByte(255);
}