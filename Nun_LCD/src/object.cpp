#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <Nunchuk.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

// defines voor nunchuck controller

#define NUNCHUK_ADDRESS 0x52
#define WAIT		1000
#define BAUDRATE	9600
#define CHUNKSIZE	32
#define BUFFERLEN	256

// defines voor LCD
#define TFT_DC 9
#define TFT_CS 10

//defines voor cicle
#define RADIUS 10	// pixels

// what to show
#define STATE

// prototypes
bool show_state(void);

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int main(int argc, char const *argv[])
{
  sei();				// enable global interrupts
	tft.begin();        // initialize the tft
  Wire.begin();
  Serial.begin(9600);			

  // stappen voor LCD
	uint16_t w = tft.width();	// tft size
	uint16_t h = tft.height();

	uint16_t c = ILI9341_MAGENTA;	// circle color
	uint16_t d = RADIUS * 2;	// circle diameter

  int XMotor = 50;
  int YMotor = 50;

	tft.fillScreen(ILI9341_BLACK);	// clear screen

    if (!Nunchuk.begin(NUNCHUK_ADDRESS))
	{
		Serial.println("******** No nunchuk found");
		Serial.flush();
		return(1);
	}

	while (1) {		
		if (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			tft.fillTriangle(XMotor, YMotor, XMotor, YMotor+10, XMotor+10, YMotor+5, 0xf800);
			if (Nunchuk.state.joy_x_axis== 00)
			{
				tft.fillTriangle(XMotor, YMotor, XMotor, YMotor+10, XMotor+10, YMotor+5, ILI9341_BLACK);
				XMotor-=5;
			} else if (Nunchuk.state.joy_x_axis== 255)
			{
				tft.fillTriangle(XMotor, YMotor, XMotor, YMotor+10, XMotor+10, YMotor+5, ILI9341_BLACK);
				XMotor+=5;
			}
			else if (Nunchuk.state.joy_y_axis== 255)
			{
				tft.fillTriangle(XMotor, YMotor, XMotor, YMotor+10, XMotor+10, YMotor+5, ILI9341_BLACK);
				YMotor-=5;
			}	
			else if (Nunchuk.state.joy_y_axis== 00)
			{
				tft.fillTriangle(XMotor, YMotor, XMotor, YMotor+10, XMotor+10, YMotor+5, ILI9341_BLACK);
				YMotor+=5;
			}
			if (XMotor < 0){
				XMotor = 0;
			}
			if (XMotor > 230){
				XMotor = 230;
			}
			if (YMotor > 310){
				YMotor = 310;
			}
			if (YMotor < 0){
				YMotor = 0;
			}
			

		}
	}
    return 0;
}
