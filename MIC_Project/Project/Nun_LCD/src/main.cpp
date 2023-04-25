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
		if (Nunchuk.state.z_button, HEX== 1)
		{
			testRects(ILI9341_GREEN);
		 	tft.fillScreen(ILI9341_BLACK);	// clear screen
		}
		
		Serial.print("\t\tBuuutton Z: ");
        Serial.println(Nunchuk.state.z_button, HEX);
        _delay_ms(500);
		if (!Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			Serial.print("\t\tButton Z: ");
			Serial.println(Nunchuk.state.z_button, HEX);
		}
		
        // if (Nunchuk.state.z_button, HEX == 1)
        // {
        //     for (uint16_t x=RADIUS; x<w; x+=d) {
		// 	for (uint16_t y=RADIUS; y<h; y+=d) {
		// 		tft.fillCircle(x, y, RADIUS, c);
		// 	}
		// }
		// tft.fillScreen(ILI9341_BLACK);	// clear screen
        //}
	}
    return 0;
}

bool show_state(void)
{
	if (!Nunchuk.getState(NUNCHUK_ADDRESS))
		return (false);
	Serial.println("------State data--------------------------");
	Serial.print("Joy X: ");
	Serial.print(Nunchuk.state.joy_x_axis, HEX);
	Serial.print("\t\tAccel X: ");
	Serial.print(Nunchuk.state.accel_x_axis, HEX);
	Serial.print("\t\tButton C: ");
	Serial.println(Nunchuk.state.c_button, HEX);

	Serial.print("Joy Y: ");
	Serial.print(Nunchuk.state.joy_y_axis, HEX);
	Serial.print("\t\tAccel Y: ");
	Serial.print(Nunchuk.state.accel_y_axis, HEX);
	Serial.print("\t\tButton Z: ");
	Serial.println(Nunchuk.state.z_button, HEX);

	Serial.print("\t\t\tAccel Z: ");
	Serial.println(Nunchuk.state.accel_z_axis, HEX);

	return(true);
}



