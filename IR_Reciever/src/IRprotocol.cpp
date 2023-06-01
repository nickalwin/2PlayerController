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
#include "IRSendCodes.h"
#include "IRReceiveCodes.h"
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
//-------------------------------------------------------------------------------------
// voor test mogelijkheden
bool algeweest = false;
bool algeweest2 = false;
bool algeweest3 = false;
bool algeweest4 = false;
bool isinterrupt = false;
//-------------------------------------------------------------------------------------
//voor sturen van Infrarood
void sendIR(long int direction[]);
int IRledPin =  6;    
bool is38khz =true; // false is 56 khz true is 38 khz
uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing
//-------------------------------------------------------------------------------------
//voor ontvangen van infrarood
int listenForIR(void);
void printBit(void);
void SendTestCode();
//-------------------------------------------------------------------------------------
//init functies
void ReadNunchuk();
void timer(uint16_t microseconds);
void initexinterupt();
void pulseIR(long microsecs);
void initpins();
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
//nunchuck


int main(int argc, char const *argv[])
{
  initpins();
  Wire.begin();
  Serial.begin(BAUDRATE);
  // een handruk om te kijken of de nunchuk er is		
	Serial.print("-------- Connecting to nunchuk at address 0x");
	Serial.println(NUNCHUK_ADDRESS, HEX);
  // als de nunchuk niet gevonden wordt
  if (!Nunchuk.begin(NUNCHUK_ADDRESS)){
    Serial.println("******** No nunchuk found");
    Serial.flush();
  }

    while (1)
    {
      if (isinterrupt) // als er een interrupt is geweest voert hij deze functie uit om ir te lezen
      {
        printBit();
        isinterrupt = false;
      }
      ReadNunchuk();
    }
    return 0;
}

ISR(INT0_vect) {
  listenForIR();
  isinterrupt = true;
  cli();
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

void sendIR(long int direction[]){
  for (int i = 0; i < 74 ; i = i + 2) // 74 is the lengt of the arrays
  {
    pulseIR(direction[i]);
    // timer(direction[i]);
    delayMicroseconds(direction[i]);
  }
}

//timer
void timer(uint16_t microseconds) {
    microseconds = (microseconds / 64);

    TCNT1 = 0;
    while (TCNT1 < microseconds)
    {
        //doe niks
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
        Serial.print('!');
        return currentpulse;
       }
    }
    pulses[currentpulse][0] = highpulse;
    while (! (IRpin_PIN & _BV(IRpin))) {
       lowpulse++;
       Serial.print(currentpulse);
        timer(RESOLUTION);
        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
          sei(); //interupts aan
          Serial.print('!');
          Serial.print(currentpulse);
          return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;
    currentpulse++;
  }
}

void printBit(){
      int firstpulse;
      int secondpulse;
      int total;
      int count = 0;
      Serial.println("Received:");
      for (uint8_t i = 0; i < currentpulse; i++) {
        firstpulse = pulses[i][0];
        secondpulse = pulses[i][1];
        total = firstpulse + secondpulse;

        //for printing bits--------------------------
        if(total > 350 && total < 390){
          Serial.print("0");
          count++;
        }

        if(total > 630 && total < 690){
          Serial.print("1");
          count++;
        }
      }
      Serial.println(count);
      Serial.println(""); 

}

void ReadNunchuk(){
  if (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			if (Nunchuk.state.joy_x_axis== 00)
			{
          if (!algeweest)
          {
          Serial.write("left");
          // sendIR(sendTop);
          SendTestCode();
          algeweest = true;
          algeweest2 = false;
          algeweest3 = false;
          algeweest4 = false;
          }
			} else if (Nunchuk.state.joy_x_axis== 255)
			{
        if (!algeweest2)
        {
          Serial.write("right");
          // sendIR(sendTop);
          SendTestCode();
          algeweest = false;
          algeweest2 = true;
          algeweest3 = false;
          algeweest4 = false;    
        }
			}
			else if (Nunchuk.state.joy_y_axis== 255)
			{
        if (!algeweest3)
        {
          Serial.write("top");
          // sendIR(sendTop);
          SendTestCode();
          algeweest = false;
          algeweest2 = false;
          algeweest3 = true;
          algeweest4 = false;    
        }
			}	
			else if (Nunchuk.state.joy_y_axis== 00)
			{
        if (!algeweest4)
        {
          Serial.write("bottom");
          // sendIR(sendTop);
          SendTestCode();
          algeweest = false;
          algeweest2 = false;
          algeweest3 = false;
          algeweest4 = true;    
        }
			}
		}
}

void SendTestCode() {

  //start

  pulseIR(9200);
  timer(4608);

  //startbit

  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(1600); // 1
  pulseIR(640); timer(1600); // 1
  pulseIR(640); timer(1600); // 1
  pulseIR(640); timer(1600); // 1
  pulseIR(640); timer(1600); // 1
  pulseIR(640); timer(1600); // 1
  pulseIR(640); timer(1600); // 1
  pulseIR(640); timer(1600); // 1

  //readable bit

  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(640); // 0
  pulseIR(640); timer(1600); // 1

  //end

  pulseIR(640);
  timer(4608);
  pulseIR(9200);

}
