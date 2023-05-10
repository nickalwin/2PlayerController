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

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(ILI9341_BLACK);
  n     = min(tft.width(), tft.height());
  //start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft.drawRect(cx-i2, cy-i2, i, i, color);
  }

  //return micros() - start;
  return 0;
}

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
			if (Nunchuk.state.joy_x_axis== 00)
			{
				tft.setCursor(0, 150);
				tft.setTextSize(2);
  				tft.println("Links");
			} else if (Nunchuk.state.joy_x_axis== 255)
			{
				tft.setCursor(150, 150);
				tft.setTextSize(2);
  			tft.println("Rechts");
			}
			else if (Nunchuk.state.joy_y_axis== 255)
			{
				tft.setCursor(100, 10);
				tft.setTextSize(2);
  				tft.println("Boven");
			}	
			else if (Nunchuk.state.joy_y_axis== 00)
			{
				tft.setCursor(100, 290);
				tft.setTextSize(2);
  			tft.println("Onder");
			}		
			tft.fillScreen(ILI9341_BLACK);
		}
	}
    return 0;
}

unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  //unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  //return micros() - start;
  return 0;
}