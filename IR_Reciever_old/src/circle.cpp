#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

#define RADIUS 10	// pixels

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int main(void)
{
	sei();				// enable global interrupts
	tft.begin();			// initialize the tft

	uint16_t w = tft.width();	// tft size
	uint16_t h = tft.height();

	uint16_t c = ILI9341_MAGENTA;	// circle color
	uint16_t d = RADIUS * 2;	// circle diameter

	tft.fillScreen(ILI9341_BLACK);	// clear screen
	while (1) 
	{
		// draw circles on screen
		for (uint16_t x=RADIUS; x<w; x+=d) {
			for (uint16_t y=RADIUS; y<h; y+=d) {
				tft.fillCircle(x, y, RADIUS, c);
			}
		}
		tft.fillScreen(ILI9341_BLACK);	// clear screen
	}
	return(0);
}
