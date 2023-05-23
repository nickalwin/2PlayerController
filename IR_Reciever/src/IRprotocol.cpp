#include <avr/io.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Wire.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Nunchuk.h>

#define IRpin_PIN      PIND
#define IRpin          2
#define MAXPULSE 65000
#define NUMPULSES 50
#define RESOLUTION 20 
#define FUZZINESS 20

//-------------------------------------------------------------------------------------
//defines for nunchuck
#define NUNCHUK_ADDRESS 0x52
#define WAIT		1000
#define BAUDRATE	9600
#define CHUNKSIZE	32
#define BUFFERLEN	256

void SendPlayCode();
void sendlinksboven();
void sendMiddenBoven();
void sendRechtsBoven();
// voor test mogelijkheden
bool algeweest = false;
bool algeweest2 = false;
bool algeweest3 = false;
bool algeweest4 = false;


int IRledPin =  6;    
bool is38khz =false; // false is 56 khz true is 38 khz

//-------------------------------------------------------------------------------------
// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

#include "IRSendCodes.h"
#include "IRReceiveCodes.h"

int listenForIR(void);
boolean IRcompare(int numpulses, int Signal[], int refsize);
unsigned long testRects(uint16_t color);
unsigned long testText();
//--------------------------------------------------
// prototypes
bool show_state(void);

int main(int argc, char const *argv[])
{
    //--------------------------------------------------
    // timer
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << TOIE1);
    //----------------------------------------------------------------

    sei();				// enable global interrupts
    Wire.begin();
    Serial.begin(BAUDRATE);			

    //-------------------------------------------------------------------

    //Serial.println("Ready to send and receive IR!");

    // handshake with nunchuk
	  Serial.println(NUNCHUK_ADDRESS, HEX);
    if (!Nunchuk.begin(NUNCHUK_ADDRESS))
    {
      Serial.println("******** No nunchuk found");
      Serial.flush();
    }


    while (1)
    {
      int numberpulses;
      numberpulses = listenForIR();

      int firstpulse;
      int secondpulse;
      int total;
      Serial.println("Received:");
      for (uint8_t i = 0; i < currentpulse; i++) {
        firstpulse = pulses[i][0];
        secondpulse = pulses[i][1];
        total = firstpulse + secondpulse;
        if(total > 320 && total < 370){
          Serial.print("0");
        }
        if(total > 630 && total < 680){
          Serial.print("1");
        }
      }

    if (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			if (Nunchuk.state.joy_x_axis== 00)
			{
          if (!algeweest)
          {
            Serial.println("Sending play button");
            // SendPlayCode();
            algeweest=true;
            algeweest2 = false;
          }
			} else if (Nunchuk.state.joy_x_axis== 255)
			{
        if (!algeweest2)
        {
          Serial.println("sending linksboven");
          // sendlinksboven();
          algeweest2=true;
          algeweest = false;
        }
			}
			else if (Nunchuk.state.joy_y_axis== 255)
			{
        if (!algeweest3)
        {
          Serial.println("sending MiddenBoven");
          // sendMiddenBoven();
          algeweest3=true;
          algeweest4 = false;    
        }
			}	
			else if (Nunchuk.state.joy_y_axis== 00)
			{
        if (!algeweest4)
        {
          Serial.println("sending RechtsBoven");
          // sendRechtsBoven();
          algeweest4 = true;
          algeweest3 = false;    
        }
			}
		}

}
    return 0;
}

void timer(int miliseconds){
    TCNT1 = 0;
    while (TCNT1 < (miliseconds))
    {
        //doe niks
    }
}

void pulseIR(long microsecs) {
 
  cli();  
 
  if (is38khz)
  {
    while (microsecs > 0) {
    // 38 kHz
    DDRD |= (1 << IRledPin);  // set the LED on
    timer(10);  
    DDRD &= ~(1 << IRledPin);  // set the LED off
    timer(10);          
 
    // niet aankomen
    microsecs -= 26; 
    }
  } else if (!is38khz) {
      while (microsecs > 0) {
      // 56 kHz 
      DDRD |= (1 << IRledPin);  // set the LED on
      timer(6);         
      DDRD &= ~(1 << IRledPin);  // set the LED off
      timer(6);        
 
      // niet aankomen
      microsecs -= 26;
    }
  }
    sei();  
}

int listenForIR(void) {
  currentpulse = 0;
  
  while (1) {
    uint16_t highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length
  
    //  while (digitalRead(IRpin)) { // this is too slow!
    while (IRpin_PIN & (1 << IRpin)) {
       // pin is still HIGH

       // count off another few microseconds
       highpulse++;
      //  delayMicroseconds(RESOLUTION);
      timer((RESOLUTION/1000));
      
       // If the pulse is too long, we 'timed out' - either nothing
       // was received or the code is finished, so print what
       // we've grabbed so far, and then reset
       
       // KGO: Added check for end of receive buffer
       if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    // we didn't time out so lets stash the reading
    pulses[currentpulse][0] = highpulse;
  
    // same as above
    while (! (IRpin_PIN & _BV(IRpin))) {
       // pin is still LOW
       lowpulse++;
        //  delayMicroseconds(RESOLUTION);
        timer((RESOLUTION/1000));

        // KGO: Added check for end of receive buffer
        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;

    // we read one high-low pulse successfully, continue!
    currentpulse++;
  }
}
