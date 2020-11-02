/* 
* LEDStrip.cpp
*
* Created: 02/11/2020 09.54.40
* Author: Kaare
*/
#include "LEDStrip.h"

int size = 0;
LED **leds = malloc(0);

// default constructor
LEDStrip::LEDStrip()
{

} //LEDStrip

// default destructor
LEDStrip::~LEDStrip()
{
} //~LEDStrip

void insertLED(LED *l, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _brightness)
{
	l->r = _r;
	l->g = _g;
	l->b = _b;
	l->brightness = _brightness;
}

void addLED(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness, int position)
{
	if(position > size)
	{	
		leds = realloc(leds, position * sizeof(LED*));
		size = position;
	}
	
	insertLED(&leds[position - 1], r, g, b, brightness);
}