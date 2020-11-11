/* 
* LEDStrip.h
*
* Created: 02/11/2020 09.54.40
* Author: Kaare
*/


#ifndef __LEDSTRIP_H__
#define __LEDSTRIP_H__

#include <stdlib.h>
#include <stdint.h>
#include "avr/io.h"
#include <util/delay.h>

typedef struct
{
	uint8_t _r, _g, _b;
} LED;

class LEDStrip
{
//variables
public:
protected:
private:

//functions
public:
	LEDStrip(uint8_t rows, uint8_t columns, uint8_t br, uint8_t comms);
	~LEDStrip();
	void setLED(uint8_t pos, uint8_t r, uint8_t g, uint8_t b);
	void clearLED(uint8_t pos);
	void sendFrames();
protected:
private:
	LEDStrip( const LEDStrip &c );
	LEDStrip& operator=( const LEDStrip &c );
	void sendByte(uint8_t byte);
	void createFrame(uint8_t pos);
}; //LEDStrip

#endif //__LEDSTRIP_H__
