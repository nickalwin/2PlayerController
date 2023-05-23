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

const unsigned char SLAVE_ADDRESS = 0x42;
void init_twi();
void send_slave(unsigned char data);
void stop();
constexpr uint8_t disp[] = {
    0xC0,       // 0
    0xF9,       // 1
    0xA4,       // 2
    0xB0,       // 3
    0x99,       // 4
    0x92,       // 5
    0b10001110, // F
    0xFF,       // shows nothing
};

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

	while (1)
	{
	
	//declare change score
	void change_score(int8_t score);
	int8_t score = 0;

    if (!Nunchuk.begin(NUNCHUK_ADDRESS))
	{
		Serial.println("******** No nunchuk found");
		Serial.flush();
		return(1);
	}
while (score < 5){
	int alive = 1;
	int XMotor = 50;
	int YMotor = 50;

  	int lijn[2][128];
	int teller = 0;

  	int8_t richting = 1;
	
	change_score(score);

	tft.fillScreen(ILI9341_BLACK);	// clear screen
	tft.drawRoundRect(0, 0, w, h, 5, ILI9341_WHITE);	//draw border
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

			//timer
			TCNT1 = 0;
			TCCR1A = 0;
			TCCR1B = 0;
			TCCR1B |= (1 << CS12) | (1 << CS10);
			TIMSK1 |= (1 << TOIE1);
			sei();
			while (TCNT1 < 250)
			{
				//do nothing
			}
			if (richting == 0 || richting == 2)
			{
				tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, ILI9341_BLACK);
			}
			else if (richting == 1 || richting == 3)
			{
				tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, ILI9341_BLACK);
			}
			if(richting==1){
				XMotor+=1;
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
			if(richting==3){
				XMotor-=1;
				lijn[0][teller] = XMotor+10;
                lijn[1][teller] = YMotor+3;
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, 0xf800);
                teller++;
                if (teller == 128)
                {
                    teller = 0;
                }
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, ILI9341_BLACK);
			}
			if(richting==0){
				YMotor-=1;
				lijn[0][teller] = XMotor+3;
                lijn[1][teller] = YMotor+10;
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, 0xf800);
                teller++;
                if (teller == 128)
                {
                    teller = 0;
                }
                tft.drawLine(lijn[0][teller], lijn[1][teller],lijn[0][teller]-1, lijn[1][teller]-1, ILI9341_BLACK);
			}
			if(richting==2){
				YMotor+=1;
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
			

			if (Nunchuk.state.joy_x_axis== 00 && richting!=1)
			{
				if(richting!=3)XMotor-=10;
				richting = 3;
			} else if (Nunchuk.state.joy_x_axis== 255 && richting != 3)
			{
				if(richting!=1)XMotor+=5;
				richting = 1;
			}
			else if (Nunchuk.state.joy_y_axis== 255 && richting!= 2)
			{
				if(richting!=0)YMotor-=10;
				richting = 0;
			}	
			else if (Nunchuk.state.joy_y_axis== 00 && richting!= 0)
			{
				if(richting!=2)YMotor+=8;
				richting = 2;
			}
			if (XMotor < 0){
				alive = 0;
				XMotor = 0;
			}
			if (XMotor > (w -5)){
				alive = 0;
				XMotor = 230;
			}
			if (YMotor > (h-3)){
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
	score++;
	}
	change_score(score);
	//create game over screen
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(0, 0);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(3);
	tft.println("Game Over");
	tft.setCursor(0, 50);
	tft.setTextSize(2);
	tft.println("Score: ");
	tft.println(score);
	tft.setCursor(0, 100);
	tft.setTextSize(2);
	tft.println("Press C & Z to continue");
	//wait for button press
	while (1)
	{
		//timer
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TIMSK1 |= (1 << TOIE1);
		sei();
		while (TCNT1 < 250)
		{
			//do nothing
		}
		if (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			if (Nunchuk.state.z_button == 1 && Nunchuk.state.c_button == 1)
			{
				break;
			}
		}
	}
	}
	return 0;
}

void change_score(int8_t score)
{
	init_twi();
	send_slave(SLAVE_ADDRESS);
	send_slave(disp[score]);
	stop();
}
void init_twi() // intialiseren van registers van TWI of(I2C)
{
    TWCR = (1<<TWEN);// het aanzetten van TWI module
    TWSR = 0x00; // configureren  van prescaler
    TWBR = 255;// configureren van de clock tussen de master en de slave
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0); // Use '&' instead of '=='
}

void send_slave(unsigned char data) // data verzenden via TWDR register
{
    TWDR = data;
    TWCR = (1<<TWINT ) | (1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0); // Use '&' instead of '=='
}

void stop() // stop met verzenden
{
    TWCR = (1<<TWINT) | (1<< TWEN) | (1<<TWSTO);
}