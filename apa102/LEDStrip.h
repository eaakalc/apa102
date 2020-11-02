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

typedef struct
{
	uint8_t r, g, b, brightness;
	LED(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _brightness) : r(_r), g(_g), b(_b), brightness(_brightness){}
} LED;

class LEDStrip
{
//variables
public:
protected:
private:

//functions
public:
	LEDStrip();
	~LEDStrip();
	void addLED(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness, int position);
	void removeLED(int position);
	void updateStrip();
protected:
private:
	void insertLED(LED *l, uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _brightness);
	LEDStrip( const LEDStrip &c );
	LEDStrip& operator=( const LEDStrip &c );

}; //LEDStrip

#endif //__LEDSTRIP_H__
