/* 
* LEDStrip.cpp
*
* Created: 02/11/2020 09.54.40
* Author: Kaare
*/
#include "LEDStrip.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef LEDSIZE
#define LEDSIZE 1024
#endif

int size = 0;
uint8_t useSPI = 0;
uint8_t brightness;
uint8_t leds[LEDSIZE];
uint8_t maxpos;

LEDStrip::LEDStrip(uint8_t rows, uint8_t columns, uint8_t br, uint8_t comms)
{
	if(br < 32)
		brightness = br;
	else
		brightness = 31;
	
	maxpos = rows * columns;
	
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
	
	for (int i = 0; i < rows * columns; i++)
	{
		setLED(i, 0, 0, 0);
	}
}

LEDStrip::~LEDStrip()
{

}

void LEDStrip::setLED(uint8_t pos, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t position = pos + ((pos - 1) * 2);
	
	leds[position] = r;
	leds[position + 1] = g;
	leds[position + 2] = b;
}

void LEDStrip::clearLED(uint8_t pos)
{
	uint8_t position = pos + ((pos - 1) * 2);
	
	leds[position] = 0;
	leds[position + 1] = 0;
	leds[position + 2] = 0;
}

void LEDStrip::setBrightness(uint8_t br)
 {
	 if(br < 32)
	 	brightness = br;
	 else
	 	brightness = 31;
 }

void LEDStrip::sendByte(uint8_t byte)
{
	uint8_t data = byte;
	
	if(useSPI)
	{
		SPDR = data;
	
		while(!(SPSR & (1 << SPIF)));
	}
	else
	{
		//For each bit in a byte
		for (int i = 0; i < 8; i++)
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
}

void LEDStrip::Update()
{
	sendByte(0);
	sendByte(0);
	sendByte(0);
	sendByte(0);
	
	for (uint8_t i = 0; i <= maxpos * 3; i += 3)
	{
		sendByte(224 + brightness);
		sendByte(leds[i + 1]);
		sendByte(leds[i + 2]);
		sendByte(leds[i + 3]);
	}
	
	sendByte(255);
	sendByte(255);
	sendByte(255);
	sendByte(255);
}