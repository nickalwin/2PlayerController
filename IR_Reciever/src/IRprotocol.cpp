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
<<<<<<< Updated upstream
#include "IRSendCodes.h"
#include "IRReceiveCodes.h"
#define IRpin_PIN      PIND
#define IRpin          2
#define MAXPULSE 65000
#define NUMPULSES 50
#define RESOLUTION 20 
#define FUZZINESS 20
=======

>>>>>>> Stashed changes
//-------------------------------------------------------------------------------------
//defines for nunchuck
#define NUNCHUK_ADDRESS 0x52
#define WAIT		1000
#define BAUDRATE	9600
#define CHUNKSIZE	32
#define BUFFERLEN	256
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
//-------------------------------------------------------------------------------------
// voor test mogelijkheden
bool algeweest = false;
bool algeweest2 = false;
bool algeweest3 = false;
bool algeweest4 = false;
<<<<<<< Updated upstream
bool isinterrupt = false;
=======
volatile bool isinterrupt = false;

>>>>>>> Stashed changes
//-------------------------------------------------------------------------------------
//voor sturen van Infrarood
void sendIR(long int direction[]);
int IRledPin =  6;    
bool is38khz =true; // false is 56 khz true is 38 khz
<<<<<<< Updated upstream
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
=======

volatile uint16_t highCounter = 0;
volatile uint16_t lowCounter = 0;
volatile uint32_t counter = 0;
volatile uint32_t bitarraycounter = 0;
volatile bool fullbit = false;
volatile bool validbit = false;
int pulsearray[17];
int bitarray[16];

void convertArray();
void printbit();
void ReadNunchuk();
void compareBit();

void SendLeftCode();
void SendRightCode();
void SendBottomCode();
void SendTopCode();

void PulseIR();
void timer(uint16_t microseconds);

// interrupt for receiving IR

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
            isinterrupt = true;
        }
    }
    else
    {
        // Falling edge
    }
}

int main()
{
    Serial.begin(9600);

        bitarraycounter++;
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
    sei();

    Wire.begin();

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
        ReadNunchuk();

        // if (fullbit)
        // {
        //     for (uint16_t i = 0; i < (sizeof(pulsearray)/2); i++)
        //     {
        //         Serial.print(pulsearray[i]);
        //         Serial.print(',');
        //         pulsearray[i] = 0;
        //     }
        //     fullbit = false;
        //     Serial.println("");
        // }
        

        convertArray();
        printbit();
        // compareBit();
    }

    return 0;
}

//receiving IR

void convertArray(){
    if (fullbit)
    {
        for (uint16_t i = 0; i < (sizeof(pulsearray)/2); i++)
        {
            if (pulsearray[i] >= 7 && pulsearray[i] <= 11)
            {
                bitarray[i] = 0;
            }   else if(pulsearray[i] >= 12 && pulsearray[i] <= 16)
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

//sending IR
>>>>>>> Stashed changes

void ReadNunchuk(){
  if (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			if (Nunchuk.state.joy_x_axis== 00)
			{
          if (!algeweest)
          {
          Serial.write("left");
<<<<<<< Updated upstream
          // sendIR(sendTop);
          SendTestCode();
=======
          SendLeftCode();
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
          // sendIR(sendTop);
          SendTestCode();
=======
          SendRightCode();
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
          // sendIR(sendTop);
          SendTestCode();
=======
          SendTopCode();
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
          // sendIR(sendTop);
          SendTestCode();
=======
          SendBottomCode();
>>>>>>> Stashed changes
          algeweest = false;
          algeweest2 = false;
          algeweest3 = false;
          algeweest4 = true;    
        }
			}
		}
}
<<<<<<< Updated upstream

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

=======

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
        Serial.println("top");
    }
    else if(compareArray(bitarray,bottombit,16))
    {
        Serial.println("bottom");
    }
    else if(compareArray(bitarray,rightbit,16))
    {
        Serial.print("right");
    }
    else if(compareArray(bitarray,leftbit,16))
    {
        Serial.print("left");
    }
}


void SendLeftCode (){
  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0 
  pulseIR(1000);    
}

void SendRightCode(){
  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1  
  pulseIR(1000);   
}

void SendBottomCode(){ 

  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000);  
}

void SendTopCode(){

  // startbit
  pulseIR(9200);
  timer(1500);

  //Data

  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(2500); // 0
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000); timer(5000); // 1
  pulseIR(1000);  
>>>>>>> Stashed changes
}
