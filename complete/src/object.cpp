#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <Nunchuk.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>
#include <avr/eeprom.h>



// defines voor nunchuck controller

#define NUNCHUK_ADDRESS 0x52
#define WAIT 1000
#define BAUDRATE 9600
#define CHUNKSIZE 32
#define BUFFERLEN 256
// variable IR
void sendIR(long int direction[]);
int IRledPin =  6;    
bool is38khz =true; // false is 56 khz true is 38 khz

volatile uint16_t highCounter = 0;
volatile uint16_t lowCounter = 0;
volatile uint32_t counter = 0;
volatile uint32_t bitarraycounter = 0;
volatile bool fullbit = false;
volatile bool validbit = false;
int pulsearray[16];
int bitarray[16];

uint16_t pulseir;
uint16_t zerotimer;
uint16_t onetimer;
uint8_t minzeropulse;
uint8_t maxzeropulse;
uint8_t minonepulse;
uint8_t maxonepulse;
void timer(uint16_t microseconds);
// functies IR
void convertArray();
void printbit();
void ReadNunchuk();
void compareBit();
void initIRpins();

void SendLeftCode();
void SendRightCode();
void SendBottomCode();
void SendTopCode();
void sendTestCode();

void PulseIR();
// defines voor LCD
#define TFT_DC 9
#define TFT_CS 10

// defines voor cicle
#define RADIUS 10 // pixels

// what to show
#define STATE

// prototypes
bool show_state(void);
void menu();
void game();
void highscores();
void settings();
int freeRam();

const unsigned char SLAVE_ADDRESS = 0x42;
void init_twi();
void send_slave(unsigned char data);
void stop();
constexpr uint8_t disp[] = {
	0xC0,		// 0
	0xF9,		// 1
	0xA4,		// 2
	0xB0,		// 3
	0x99,		// 4
	0x92,		// 5
	0b10001110, // F
	0xFF,		// shows nothing
};

	// stappen voor LCD
	Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
	uint16_t w = tft.width(); // tft size
	uint16_t h = tft.height();
	
	int8_t score; //score
	int8_t score2; //score
	// declare change score
	void change_score(int8_t score);

	//array with colors
	uint16_t colors[7] = {ILI9341_RED, ILI9341_BLUE, ILI9341_GREEN, ILI9341_YELLOW, ILI9341_CYAN, ILI9341_MAGENTA, ILI9341_WHITE};
	//player color
	int8_t player_color = 0;
	int8_t player2_color = random(0, ((sizeof(colors)/2)-1));

int main(int argc, char const *argv[])
{
	sei();		 // enable global interrupts
	tft.begin(); // initialize the tft
	Wire.begin();
	Serial.begin(9600);

	bitarraycounter++;

	if (!Nunchuk.begin(NUNCHUK_ADDRESS))
	{
		Serial.println("******** No nunchuk found");
		Serial.flush();
		return (1);
	}
	if (is38khz)
    {
        Serial.println("38khz");
        pulseir = 1000;
        zerotimer = 2500;
        onetimer = 5000;
        minzeropulse = 10;
        maxzeropulse = 17;
        minonepulse = 18;
        maxonepulse = 25;
    }
    else
    {
        Serial.println("56khz");
        pulseir = 1500;
        zerotimer = 4000;
        onetimer = 8000;
        minzeropulse = 7;
        maxzeropulse = 11;
        minonepulse = 12;
        maxonepulse = 16;
    }
	
	menu();
}

ISR(INT0_vect)
{
    if (PIND & (1 << PD2))
    {   if(TCNT1 > 2000){
            bitarraycounter = 0;
        }
        else
        {
            pulsearray[bitarraycounter] = TCNT1;
            bitarraycounter++;
        }
        TCNT1 = 0;
        if (bitarraycounter == 16)
        {
            fullbit = true;
        }
    }
    else
    {
        // Falling edge
    }
}

void initIRpins(){
	    // Configure INT0 pin as input
    DDRD &= ~(1 << DDD2);

    // Enable external interrupt 0 on any change
    EICRA |= (1 << ISC00);

    // Enable external interrupt 0
    EIMSK |= (1 << INT0);


    // ------------------------------------------------------------------------------------------
    // init timer 1
    TCCR1B = (1 << CS10) | (1 << CS12);  // Set prescaler to 1024
    TCNT1 = 0;

    //-------------------------------------------------------------------------------------------
    // init timer 2
    TCCR2B = (1 << CS10) | (1 << CS12);
    TCNT2 = 0;
}

void convertArray(){
    if (fullbit)
    {
        for (uint16_t i = 0; i < (sizeof(pulsearray)/2); i++)
        {
            if (pulsearray[i] >= minzeropulse && pulsearray[i] <= maxzeropulse)
            {
                bitarray[i] = 0;
            }   else if(pulsearray[i] >= minonepulse && pulsearray[i] <= maxonepulse)
            {
                bitarray[i] = 1;
            }
            pulsearray[i] = 0;
        }
        if ((sizeof(bitarray)/2) == 16)
        {
            validbit = true;
        }
    }
}

int compareArray(int arr1[], int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

void printbit(){
    if (validbit)
    {    
        compareBit();

        validbit = false;
        fullbit = false;
    }   
}

void pulseIR(long microsecs) {
 
  cli();  
 
  if (is38khz)
  {
    while (microsecs > 0) {
      // 38 kHz
      PORTD |= (1 << IRledPin);  // duurt 3 microseconds
      timer(10);       
      PORTD &= ~(1 << IRledPin); // duurt 3 microseconds     
      timer(10);
      // niet aankomen
      microsecs -= 26; 
    }
  } else if (!is38khz) {
      while (microsecs > 0) {
      // 56 kHz 
      PORTD |= (1 << IRledPin);  // duurt 3 microseconds        
      timer(6);
      PORTD &= ~(1 << IRledPin);  
      timer(6);     
      // niet aankomen
      microsecs -= 26;
    }
  }
    sei();  
}

void timer(uint16_t microseconds) {
    //timer for delays
    microseconds = (microseconds / 64);

    TCNT2 = 0;
    while (TCNT2 < microseconds)
    {
        //doe niks
    }
}

int topbit[]    {1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1};
int bottombit[] {0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,0};
int rightbit[]  {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
int leftbit[]   {1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0};

void compareBit()
{
    if (compareArray(bitarray,topbit,16))
    {
        Serial.println("Receiver: top");
    }
    else if(compareArray(bitarray,bottombit,16))
    {
        Serial.println("Receiver: bottom");
    }
    else if(compareArray(bitarray,rightbit,16))
    {
        Serial.println("Receiver: right");
    }
    else if(compareArray(bitarray,leftbit,16))
    {
        Serial.println("Receiver: left");
    }
}

void menu()
{
	//free ram of heap
	freeRam();
	// option
	int8_t option = 0;
	//clear score board
	change_score(7);
	//make sure player 2 has a different color than player 1
	while (player2_color == player_color)
	{
		player2_color = random(0, ((sizeof(colors)/2)-1));
	}

	// start screen
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(0, 0);
	tft.setTextColor(colors[player_color]);
	tft.setTextSize(3);
	tft.println("Tron");
	tft.setCursor(0, 50);
	tft.setTextSize(2);
	tft.setTextColor(ILI9341_WHITE);
	tft.println("Press C & Z to start");
	// add 3 options to select from with arrow
	tft.setCursor(20, 100);
	tft.setTextSize(2);
	tft.println("1. Start");
	tft.setCursor(20, 150);
	tft.println("2. Highscores");
	tft.setCursor(20, 200);
	tft.println("3. Settings");

	// draw triangle to select option
	tft.fillTriangle(0, 100, 0, 130, 20, 115, colors[player_color]);

	if (!Nunchuk.begin(NUNCHUK_ADDRESS))
	{
		Serial.println("******** No nunchuk found");
		Serial.flush();
	}

	// wait for button press
	while (Nunchuk.getState(NUNCHUK_ADDRESS))
	{	
		if (Nunchuk.state.z_button == 1 && Nunchuk.state.c_button == 1)
		{
			if (option == 0)
				game();
			if (option == 1)
				highscores();
			if (option == 2)
				settings();

			break;
		}
		// move triangle up
		else if (Nunchuk.state.joy_y_axis == 255 && option != 0)
		{
			tft.fillTriangle(0, 100 + (option * 50), 0, 130 + (option * 50), 20, 115 + (option * 50), ILI9341_BLACK);
			option--;
			tft.fillTriangle(0, 100 + (option * 50), 0, 130 + (option * 50), 20, 115 + (option * 50), colors[player_color]);

			while (Nunchuk.getState(NUNCHUK_ADDRESS))
			{
				if (Nunchuk.state.joy_y_axis < 200)
				{
					break;
				}
			}
		}
		// move triangle down
		else if (Nunchuk.state.joy_y_axis == 00 && option != 2)
		{
			tft.fillTriangle(0, 100 + (option * 50), 0, 130 + (option * 50), 20, 115 + (option * 50), ILI9341_BLACK);
			option++;
			tft.fillTriangle(0, 100 + (option * 50), 0, 130 + (option * 50), 20, 115 + (option * 50), colors[player_color]);

			while (Nunchuk.getState(NUNCHUK_ADDRESS))
			{
				if (Nunchuk.state.joy_y_axis > 50)
				{
					break;
				}
			}
		}
	}
}
void game()
{
	//free ram of heap
	freeRam();
	score = 0;
	while (score < 5 && score2 < 5)
	{
		int alive = 1;
		int XMotor = 50;
		int YMotor = 50;

		int lijn[2][128];
		int teller = 0;


		int alive2 = 1;
		int XMotor2 = 100;
		int YMotor2 = 100;

		int lijn2[2][128];
		int teller2 = 0;


		int8_t richting = 1;
		int8_t richting2 = 0;

		change_score(score);

		tft.fillScreen(ILI9341_BLACK);					 // clear screen
		tft.drawRoundRect(0, 0, w, h, 5, ILI9341_WHITE); // draw border
		while (alive&&alive2)
		{
			if (Nunchuk.getState(NUNCHUK_ADDRESS))
			{
				if (richting == 0 || richting == 2)
				{
					tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, colors[player_color]);
				}
				else if (richting == 1 || richting == 3)
				{
					tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, colors[player_color]);
				}
				if (richting2 == 0 || richting2 == 2)
				{
					tft.fillRoundRect(XMotor2, YMotor2, 5, 10, 5, colors[player2_color]);
				}
				else if (richting2 == 1 || richting2 == 3)
				{
					tft.fillRoundRect(XMotor2, YMotor2, 10, 5, 5, colors[player2_color]);
				}

				// timer
				TCNT1 = 0;
				TCCR1A = 0;
				TCCR1B = 0;
				TCCR1B |= (1 << CS12) | (1 << CS10);
				TIMSK1 |= (1 << TOIE1);
				sei();
				while (TCNT1 < 250)
				{
					// do nothing
				}
				//stop timer
				TCCR1B = 0;
				if (richting == 0 || richting == 2)
				{
					tft.fillRoundRect(XMotor, YMotor, 5, 10, 5, ILI9341_BLACK);
				}
				else if (richting == 1 || richting == 3)
				{
					tft.fillRoundRect(XMotor, YMotor, 10, 5, 5, ILI9341_BLACK);
				}
				if (richting == 1)
				{
					XMotor += 1;
					lijn[0][teller] = XMotor;
					lijn[1][teller] = YMotor + 3;
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, colors[player_color]);
					teller++;
					if (teller == 128)
					{
						teller = 0;
					}
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, ILI9341_BLACK);
					SendRightCode();
				}
				if (richting == 3)
				{
					XMotor -= 1;
					lijn[0][teller] = XMotor + 10;
					lijn[1][teller] = YMotor + 3;
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, colors[player_color]);
					teller++;
					if (teller == 128)
					{
						teller = 0;
					}
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, ILI9341_BLACK);
					SendLeftCode();
				}
				if (richting == 0)
				{
					YMotor -= 1;
					lijn[0][teller] = XMotor + 3;
					lijn[1][teller] = YMotor + 10;
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, colors[player_color]);
					teller++;
					if (teller == 128)
					{
						teller = 0;
					}
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, ILI9341_BLACK);
					SendTopCode();
				}
				if (richting == 2)
				{
					YMotor += 1;
					lijn[0][teller] = XMotor + 3;
					lijn[1][teller] = YMotor;
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, colors[player_color]);
					teller++;
					if (teller == 128)
					{
						teller = 0;
					}
					tft.drawLine(lijn[0][teller], lijn[1][teller], lijn[0][teller] - 1, lijn[1][teller] - 1, ILI9341_BLACK);
					SendBottomCode();
				}

				if (Nunchuk.state.joy_x_axis == 00 && richting != 1)
				{
					if (richting != 3)
						XMotor -= 10;
					richting = 3;
				}
				else if (Nunchuk.state.joy_x_axis == 255 && richting != 3)
				{
					if (richting != 1)
						XMotor += 5;
					richting = 1;
				}
				else if (Nunchuk.state.joy_y_axis == 255 && richting != 2)
				{
					if (richting != 0)
						YMotor -= 10;
					richting = 0;
				}
				else if (Nunchuk.state.joy_y_axis == 00 && richting != 0)
				{
					if (richting != 2)
						YMotor += 8;
					richting = 2;
				}
				if (XMotor < 0)
				{
					alive = 0;
					XMotor = 0;
				}
				if (XMotor > (w - 5))
				{
					alive = 0;
					XMotor = 230;
				}
				if (YMotor > (h - 3))
				{
					alive = 0;
					YMotor = 310;
				}
				if (YMotor < 0)
				{
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
			//player 2
				if (richting2 == 0 || richting2 == 2)
				{
					tft.fillRoundRect(XMotor2, YMotor2, 5, 10, 5, ILI9341_BLACK);
				}
				else if (richting2 == 1 || richting2 == 3)
				{
					tft.fillRoundRect(XMotor2, YMotor2, 10, 5, 5, ILI9341_BLACK);
				}
				if (richting2 == 1)
				{
					XMotor2 += 1;
					lijn2[0][teller2] = XMotor2;
					lijn2[1][teller2] = YMotor2 + 3;
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, colors[player2_color]);
					teller2++;
					if (teller2 == 128)
					{
						teller2 = 0;
					}
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, ILI9341_BLACK);
				}
				if (richting2 == 3)
				{
					XMotor2 -= 1;
					lijn2[0][teller2] = XMotor2 + 10;
					lijn2[1][teller2] = YMotor2 + 3;
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, colors[player2_color]);
					teller2++;
					if (teller2 == 128)
					{
						teller2 = 0;
					}
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, ILI9341_BLACK);
				}
				if (richting2 == 0)
				{
					YMotor2 -= 1;
					lijn2[0][teller2] = XMotor2 + 3;
					lijn2[1][teller2] = YMotor2 + 10;
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, colors[player2_color]);
					teller2++;
					if (teller2 == 128)
					{
						teller2 = 0;
					}
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, ILI9341_BLACK);
				}
				if (richting2 == 2)
				{
					YMotor2 += 1;
					lijn2[0][teller2] = XMotor2 + 3;
					lijn2[1][teller2] = YMotor2;
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, colors[player2_color]);
					teller2++;
					if (teller2 == 128)
					{
						teller2 = 0;
					}
					tft.drawLine(lijn2[0][teller2], lijn2[1][teller2], lijn2[0][teller2] - 1, lijn2[1][teller2] - 1, ILI9341_BLACK);
				}

				if (compareArray(bitarray,rightbit,16) && richting2 != 1)
				{
					if (richting2 != 3)
						XMotor2 -= 10;
					richting2 = 3;
				}
				else if (compareArray(bitarray,leftbit,16) && richting2 != 3)
				{
					if (richting2 != 1)
						XMotor2 += 5;
					richting2 = 1;
				}
				else if (compareArray(bitarray,bottombit,16) && richting2 != 2)
				{
					if (richting2 != 0)
						YMotor2 -= 10;
					richting2 = 0;
				}
				else if (compareArray(bitarray,topbit,16) && richting2 != 0)
				{
					if (richting2 != 2)
						YMotor2 += 8;
					richting2 = 2;
				}
				if (XMotor2 < 0)
				{
					alive2 = 0;
					XMotor2 = 0;
				}
				if (XMotor2 > (w - 5))
				{
					alive2 = 0;
					XMotor2 = 230;
				}
				if (YMotor2 > (h - 3))
				{
					alive2 = 0;
					YMotor2 = 310;
				}
				if (YMotor2 < 0)
				{
					alive2 = 0;
					YMotor2 = 0;
				}
				for (int i = 0; i < lijn2[0][teller2]; i++)
				{
					if (XMotor2 == lijn2[0][i] && YMotor2 == lijn2[1][i])
					{
						alive2 = 0;
					}
				}
			
		}
		if (!alive)
		{
			score++;
		}
		if (!alive2)
		{
			score2++;
		}
	}
	change_score(score);
	//write score to avr eeprom
	eeprom_write_byte((uint8_t*)0, score);
	eeprom_write_byte((uint8_t*)1, score2);

	// create game over screen
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(0, 0);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(3);
	tft.println("Game Over");
	tft.setCursor(0, 100);
	tft.setTextSize(2);
	tft.println("Press C & Z to continue");
	// wait for button press
	while (1)
	{
		// timer
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TIMSK1 |= (1 << TOIE1);
		sei();
		while (TCNT1 < 250)
		{
			// do nothing
		}
		//stop timer
		TCCR1B = 0;
		while (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			// timer
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TIMSK1 |= (1 << TOIE1);
		sei();
		while (TCNT1 < 250)
		{
			// do nothing
		}
		//stop timer
		TCCR1B = 0;
			if (Nunchuk.state.z_button == 1 && Nunchuk.state.c_button == 1)
			{
				while (Nunchuk.getState(NUNCHUK_ADDRESS))
				{
					// timer
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TIMSK1 |= (1 << TOIE1);
		sei();
		while (TCNT1 < 250)
		{
			// do nothing
		}
		//stop timer
		TCCR1B = 0;
					if (Nunchuk.state.z_button == 0 && Nunchuk.state.c_button == 0)
					{
						menu();
					}
				}
			}
		}
	}
}
void highscores()
{
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(0, 0);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(3);
	tft.println("Highscores");
	//read score from avr eeprom
	int8_t score = eeprom_read_byte((uint8_t*)0);
	int8_t score2 = eeprom_read_byte((uint8_t*)1);
	//show score of player 1
	tft.setCursor(0, 50);
	tft.setTextSize(2);
	tft.println("Player 1: ");
	tft.setCursor(120, 50);
	tft.print(score);
	//show score of player 2
	tft.setCursor(0, 100);
	tft.setTextSize(2);
	tft.println("Player 2: ");
	tft.setCursor(120, 100);
	tft.print(score2);

	tft.setCursor(0, 200);
	tft.setTextSize(2);
	tft.println("Press C & Z to continue");
	// wait for button press
	while (1)
	{
		// timer
		TCNT1 = 0;
		TCCR1A = 0;
		TCCR1B = 0;
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TIMSK1 |= (1 << TOIE1);
		sei();
		while (TCNT1 < 250)
		{
			// do nothing
		}
		//stop timer
		TCCR1B = 0;
		while (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			if (Nunchuk.state.z_button == 0 && Nunchuk.state.c_button == 0)
			{
				while (Nunchuk.getState(NUNCHUK_ADDRESS))
				{
					if (Nunchuk.state.z_button == 1 && Nunchuk.state.c_button == 1)
					{
						menu();
					}
				}
			}
		}
	}
}

void settings(){
	//screen to select color of the player
	tft.fillScreen(ILI9341_BLACK);
	tft.setCursor(0, 0);
	tft.setTextColor(ILI9341_WHITE);
	tft.setTextSize(3);
	tft.println("Settings");
	tft.setCursor(0, 50);
	tft.setTextSize(2);
	tft.println("Press C & Z to select");
	//for loop to show all colors
	for (int i = 0; i < (sizeof(colors)/2); i++)
	{
		tft.setCursor(50, 108+(i*18));
		tft.setTextColor(colors[i]);
		tft.println("select color");
	}

	// draw triangle to select option
	tft.fillTriangle(0, 100 + (player_color * 18), 0, 130 + (player_color * 18), 20, 115 + (player_color * 18), colors[player_color]);
	if (!Nunchuk.begin(NUNCHUK_ADDRESS))
	{
		Serial.println("******** No nunchuk found");
		Serial.flush();
	}

	// wait for button press
	while (Nunchuk.getState(NUNCHUK_ADDRESS))
	{
		if (Nunchuk.state.z_button == 1 && Nunchuk.state.c_button == 1)
		{
			menu();
		}
		// move triangle up
		else if (Nunchuk.state.joy_y_axis == 255 && player_color != 0)
		{
			tft.fillTriangle(0, 100 + (player_color * 18), 0, 130 + (player_color * 18), 20, 115 + (player_color * 18), ILI9341_BLACK);
			player_color--;
			tft.fillTriangle(0, 100 + (player_color * 18), 0, 130 + (player_color * 18), 20, 115 + (player_color * 18), colors[player_color]);

			while (Nunchuk.getState(NUNCHUK_ADDRESS))
			{
				if (Nunchuk.state.joy_y_axis < 200)
				{
					break;
				}
			}
		}
		// move triangle down
		else if (Nunchuk.state.joy_y_axis == 00 && player_color != (sizeof(colors)/2)-1)
		{
			tft.fillTriangle(0, 100 + (player_color * 18), 0, 130 + (player_color * 18), 20, 115 + (player_color * 18), ILI9341_BLACK);
			player_color++;
			tft.fillTriangle(0, 100 + (player_color * 18), 0, 130 + (player_color * 18), 20, 115 + (player_color * 18), colors[player_color]);

			while (Nunchuk.getState(NUNCHUK_ADDRESS))
			{
				if (Nunchuk.state.joy_y_axis > 50)
				{
					break;
				}
			}
		}
	}
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
	TWCR = (1 << TWEN); // het aanzetten van TWI module
	TWSR = 0x00;		// configureren  van prescaler
	TWBR = 255;			// configureren van de clock tussen de master en de slave
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0)
		; // Use '&' instead of '=='
}

void send_slave(unsigned char data) // data verzenden via TWDR register
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while ((TWCR & (1 << TWINT)) == 0)
		; // Use '&' instead of '=='
}

void stop() // stop met verzenden
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
//create deleta ram function
int freeRam()
{
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void SendLeftCode (){
  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0 
  pulseIR(pulseir);    
}

void SendRightCode(){
  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1  
  pulseIR(pulseir);   
}

void SendBottomCode(){ 

  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir);  
}

void SendTopCode(){

  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(zerotimer); // 0
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir); timer(onetimer); // 1
  pulseIR(pulseir);  
}