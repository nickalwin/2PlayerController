/* Raw IR commander
 
 This sketch/program uses the Arduno and a PNA4602 to 
 decode IR received.  It then attempts to match it to a previously
 recorded IR signal
 
 Code is public domain, check out www.ladyada.net and adafruit.com
 for more tutorials! 
 */

#include <avr/io.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// Digital pin #2 is the same as Pin D2 see
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
#define IRpin_PIN      PIND
#define IRpin          2

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000
#define NUMPULSES 50

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20 

// What percent we will allow in variation to match the same code
#define FUZZINESS 20
//--------------------------------------------------------------------------------------
// defines voor nunchuck controller

// defines voor LCD
#define TFT_DC 9
#define TFT_CS 10

//defines voor cicle
#define RADIUS 10	// pixels

// what to show
#define STATE

//-------------------------------------------------------------------------------------
// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

int listenForIR(void);
void initpins();
void timer(uint16_t microseconds); 
boolean IRcompare(int numpulses, int Signal[], int refsize);
unsigned long testRects(uint16_t color);
unsigned long testText();
int IRledPin =  6;  
//--------------------------------------------------
// prototypes
bool show_state(void);

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//--------------------------------------------------
int main(int argc, char const *argv[])
{
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
  initpins();
  Wire.begin();		

  // stappen voor LCD
	uint16_t w = tft.width();	// tft size
	uint16_t h = tft.height();

	uint16_t c = ILI9341_MAGENTA;	// circle color
	uint16_t d = RADIUS * 2;	// circle diameter

	tft.fillScreen(ILI9341_BLACK);	// clear screen
  //-------------------------------------------------------------------

  while (1)
  {
    int numberpulses;
    numberpulses = listenForIR();
    Serial.println();
    Serial.println("IR Begin");
    Serial.println();
  }
}

//KGO: added size of compare sample. Only compare the minimum of the two
boolean IRcompare(int numpulses, int Signal[], int refsize) {
  int count = min(numpulses,refsize);
  for (int i=0; i< count-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    
#ifdef DEBUG    
    Serial.print(oncode); // the ON signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
#endif   
    
    // check to make sure the error is less than FUZZINESS percent
    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
#ifdef DEBUG
      Serial.print(" (ok)");
#endif
    } else {
#ifdef DEBUG
      Serial.print(" (x)");
#endif
      // we didn't match perfectly, return a false match
      return false;
    }
    
    
#ifdef DEBUG
    Serial.print("  \t"); // tab
    Serial.print(offcode); // the OFF signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
#endif    
    
    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
#ifdef DEBUG
      Serial.print(" (ok)");
#endif
    } else {
#ifdef DEBUG
      Serial.print(" (x)");
#endif
      // we didn't match perfectly, return a false match
      return false;
    }
    
#ifdef DEBUG
    Serial.println();
#endif
  }
  // Everything matched!
  return true;
}

int listenForIR(void) {
  // cli(); //interupts uit
  Serial.print('.');
  currentpulse = 0;
  
  while (1) {
    uint16_t highpulse, lowpulse;
    highpulse = lowpulse = 0;
    Serial.print('/');
    while (IRpin_PIN & (1 << IRpin)) {
      highpulse++;
      timer(RESOLUTION); // dit is een delay van 20 microseconden
      if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) { // als de highpulse groter is dan 65000 en de currentpulse niet 0 is of de currentpulse is 50
        sei(); //interupts aan
        Serial.print(currentpulse);
        Serial.print('!');
        return currentpulse;
       }
    }
    pulses[currentpulse][0] = highpulse;
    while (! (IRpin_PIN & _BV(IRpin))) {
       lowpulse++;
        timer(RESOLUTION);
        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
          sei(); //interupts aanint listenForIR(void)
          Serial.print('!');
          Serial.print(currentpulse);
          return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;
    currentpulse++;
  }
}

void initpins(){
  // init interrupt
  // set pin 2 to trigger an interrupt on high-to-low transitions using bitwise operator
  EICRA |= (1 << ISC01);
  // set external interrupt mask register to enable pin 2
  EIMSK |= (1 << INT0);
  // ------------------------------------------------------------------------------------------
  // init timer 1
  TCCR1B = (1 << CS10) | (1 << CS12);  // Set prescaler to 1024
  TCNT1 = 0;
  sei();
  // ------------------------------------------------------------------------------------------
  //init IR led IR reciever
  DDRD &= ~(1 << IRpin); // Set pin 2 as input
  DDRD |= (1 << IRledPin); // Set pin 6 as output
}

void timer(uint16_t microseconds) {
    microseconds = (microseconds / 64);

    TCNT1 = 0;
    while (TCNT1 < microseconds)
    {
        //doe niks
    }
}




// methodes om te helpen ----------------------------------------------------------------------------------

// void printpulses(void) {
  // Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  // for (uint8_t i = 0; i < currentpulse; i++) {
  //   Serial.print(pulses[i][0] * RESOLUTION, DEC);
  //   Serial.print(" usec, ");
  //   Serial.print(pulses[i][1] * RESOLUTION, DEC);
  //   Serial.println(" usec");
  // }

  // print it in a 'array' format>
  // Serial.println("int IRsignal[] = {");
  // Serial.println("// ON, OFF ");
  // for (uint8_t i = 0; i < currentpulse-1; i++) {
  //   //Serial.print("\t"); // tab
  //   Serial.print("pulseIR(");
  //   Serial.print(pulses[i][1] * RESOLUTION , DEC);
  //   Serial.print(");");
  //   Serial.println("");
  //   //Serial.print("\t");
  //   Serial.print("delayMicroseconds(");
  //   Serial.print(pulses[i+1][0] * RESOLUTION , DEC);
  //   Serial.println(");");
  // }

  // //Serial.print("\t"); // tab
  // Serial.print("pulseIR(");
  // Serial.print(pulses[currentpulse-1][1] * RESOLUTION, DEC);
  // Serial.print(");");

  
//   // print it in a 'array' format
//   Serial.println("int IRsignal[] = {");
//   Serial.println("// ON, OFF (in 10's of microseconds)");
//   for (uint8_t i = 0; i < currentpulse-1; i++) {
//     Serial.print("\t"); // tab
//     Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
//     Serial.print(", ");
//     Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
//     Serial.println(",");
//   }
//   Serial.print("\t"); // tab
//   Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
//   Serial.print(", 0};");
// }

// unsigned long testRects(uint16_t color) {
//   unsigned long start;
//   int           n, i, i2,
//                 cx = tft.width()  / 2,
//                 cy = tft.height() / 2;

//   tft.fillScreen(ILI9341_BLACK);
//   n     = min(tft.width(), tft.height());
//   //start = micros();
//   for(i=2; i<n; i+=6) {
//     i2 = i / 2;
//     tft.drawRect(cx-i2, cy-i2, i, i, color);
//   }

//   //return micros() - start;
//   return 0;
// }>icros();
//   tft.setCursor(0, 0);
//   tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
//   tft.println("Hello World!");
//   tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
//   tft.println(1234.56);
//   tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
//   tft.println(0xDEADBEEF, HEX);
//   tft.println();
//   tft.setTextColor(ILI9341_GREEN);
//   tft.setTextSize(5);
//   tft.println("Groop");
//   tft.setTextSize(2);
//   tft.println("I implore thee,");
//   tft.setTextSize(1);
//   tft.println("my foonting turlingdromes.");
//   tft.println("And hooptiously drangle me");
//   tft.println("with crinkly bindlewurdles,");
//   tft.println("Or I will rend thee");
//   tft.println("in the gobberwarts");
//   tft.println("with my blurglecruncheon,");
//   tft.println("see if I don't!");
//   //return micros() - start;
//   return 0;
// }
