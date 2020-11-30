/*
 * apa102.cpp
 *
 * Created: 02/11/2020 09.20.53
 * Author : Kaare
 */ 

#include <avr/io.h>

#define LEDSIZE 2000
#include "LEDStrip.h"
LEDStrip *LEDtest = new LEDStrip(8, 8, 15, 0);

#define LEDSIZE 2000
#define F_CPU 1000000UL

void * operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void * ptr)
{
	free(ptr);
}

int main(void)
{
	uint8_t rows = 8;
	uint8_t cols = 8;
	
	//Initialize LEDStrip object with 8 row & columns, brightness at 0, using SPI
	LEDStrip *LEDtest = new LEDStrip(rows, cols, 0, 1);
	
	//Running this code will set the LEDs to show a gradient
	for(int i = 1; i <= rows * cols; i++)
	{
		LEDtest->setLED(i, i, i * 2, i * 3);
	}
	
	LEDtest->Update();

	//Turns up the brightness to full step-by-step
	for (int i = 1; i < 32; i++)
	{
		LEDtest->setBrightness(i);
		LEDtest->Update();
		_delay_ms(100);
	}
	
	//Turns off LED 10
	LEDtest->clearLED(10);
	LEDtest->Update();
}

