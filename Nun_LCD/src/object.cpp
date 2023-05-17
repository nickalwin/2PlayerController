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

    if (!Nunchuk.begin(NUNCHUK_ADDRESS))
	{
		Serial.println("******** No nunchuk found");
		Serial.flush();
		return(1);
	}
while (1){
	int alive = 1;
	int XMotor = 50;
	int YMotor = 50;

  	int lijn[2][128];
	int teller = 0;

  	int8_t richting = 1;

	tft.fillScreen(ILI9341_BLACK);	// clear screen
	while (alive) {		
		if (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			/* tft.drawPixel(XMotor, YMotor, 0Xbdd7);
			tft.drawPixel(XMotor, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor, YMotor+3, 0Xbdd7);
			tft.drawPixel(XMotor-1, YMotor, 0Xbdd7);
			tft.drawPixel(XMotor-1, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-1, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-1, YMotor+3, 0Xbdd7);
			tft.drawPixel(XMotor-2, YMotor, 0Xbdd7);
			tft.drawPixel(XMotor-2, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-2, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-2, YMotor+3, 0Xbdd7);
			tft.drawPixel(XMotor-3, YMotor, 0Xf800);
			tft.drawPixel(XMotor-3, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-3, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-3, YMotor+3, 0Xf800);
			tft.drawPixel(XMotor-4, YMotor, 0Xf800);
			tft.drawPixel(XMotor-4, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-4, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-4, YMotor+3, 0Xf800);
			tft.drawPixel(XMotor-5, YMotor, 0Xf800);
			tft.drawPixel(XMotor-5, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-5, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-5, YMotor+3, 0Xf800);
			tft.drawPixel(XMotor-6, YMotor, 0Xf800);
			tft.drawPixel(XMotor-6, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-6, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-6, YMotor+3, 0Xf800);
			tft.drawPixel(XMotor-7, YMotor, 0Xf800);
			tft.drawPixel(XMotor-7, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-7, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-7, YMotor+3, 0Xf800);
			tft.drawPixel(XMotor-8, YMotor, 0Xbdd7);
			tft.drawPixel(XMotor-8, YMotor+1, 0Xf800);	
			tft.drawPixel(XMotor-8, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-8, YMotor+3, 0Xbdd7);
			tft.drawPixel(XMotor-9, YMotor, 0Xbdd7);
			tft.drawPixel(XMotor-9, YMotor+1, 0Xf800);
			tft.drawPixel(XMotor-9, YMotor+2, 0Xf800);
			tft.drawPixel(XMotor-9, YMotor+3, 0Xbdd7); */



			if (richting == 0 || richting == 2)
			{
				tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, 0xf800);
			}
			else if (richting == 1 || richting == 3)
			{
				tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, 0xf800);
			}
			

			if (Nunchuk.state.joy_x_axis== 00 && richting!=1)
			{
				tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, ILI9341_BLACK);
				tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, ILI9341_BLACK);
				if(richting!=3)XMotor-=10;
				else XMotor-=1;
				richting = 3;
				lijn[0][teller] = XMotor+10;
                lijn[1][teller] = YMotor+2;
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, 0xf800);
                teller++;
                if (teller == 128)
                {
                    teller = 0;
                }
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, ILI9341_BLACK);
			} else if (Nunchuk.state.joy_x_axis== 255 && richting != 3)
			{
				tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, ILI9341_BLACK);
				tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, ILI9341_BLACK);
				if(richting!=1)XMotor+=5;
				else XMotor+=1;
				richting = 1;
				lijn[0][teller] = XMotor;
                lijn[1][teller] = YMotor+3;
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, 0xf800);
                teller++;
                if (teller == 128)
                {
                    teller = 0;
                }
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, ILI9341_BLACK);
			}
			else if (Nunchuk.state.joy_y_axis== 255 && richting!= 2)
			{
				tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, ILI9341_BLACK);
				tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, ILI9341_BLACK);
				if(richting!=0)YMotor-=10;
				else YMotor-=1;
				richting = 0;
				lijn[0][teller] = XMotor+2;
                lijn[1][teller] = YMotor+10;
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, 0xf800);
                teller++;
                if (teller == 128)
                {
                    teller = 0;
                }
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, ILI9341_BLACK);
			}	
			else if (Nunchuk.state.joy_y_axis== 00 && richting!= 0)
			{
				tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, ILI9341_BLACK);
				tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, ILI9341_BLACK);
				if(richting!=2)YMotor+=8;
				else YMotor+=1;
				richting = 2;
				lijn[0][teller] = XMotor+3;
                lijn[1][teller] = YMotor;
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, 0xf800);
                teller++;
                if (teller == 128)
                {
                    teller = 0;
                }
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, ILI9341_BLACK);
			}
			if (XMotor < 0){
				alive = 0;
				XMotor = 0;
			}
			if (XMotor > tft.width()){
				alive = 0;
				XMotor = 230;
			}
			if (YMotor > tft.height()){
				alive = 0;
				YMotor = 310;
			}
			if (YMotor < 0){
				alive = 0;
				YMotor = 0;
			}
			for (int i = 0; i < lijn[0][teller]; i++)
			{
				if (XMotor == lijn[0][i] && YMotor == lijn[1][i])
				{
					alive = 0;
				}
			}
			
			

		}
	}
	}
    return 0;
}
