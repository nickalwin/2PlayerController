#include <avr/io.h>
#include <HardwareSerial.h>
#include <Arduino.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <Nunchuk.h>

//defines voor nunchuck
#define NUNCHUK_ADDRESS 0x52
#define WAIT		1000
#define BAUDRATE	9600
#define CHUNKSIZE	32
#define BUFFERLEN	256
 
int IRledPin =  6;    
bool is38khz =false; // false is 56 khz true is 38 khz
void SendPlayCode();
void sendlinksboven();
void sendMiddenBoven();
void sendRechtsBoven();
// voor test mogelijkheden
bool algeweest = false;
bool algeweest2 = false;
bool algeweest3 = false;
bool algeweest4 = false;
 
 
void setup()   {                
  // initialize the IR digital pin as an output:
  pinMode(IRledPin, OUTPUT);      
	// enable global interrupts
	sei();

	// use Serial for printing nunchuk data
	Serial.begin(BAUDRATE);

	// join I2C bus as master
	Wire.begin();

	// handshake with nunchuk
	Serial.print("-------- Connecting to nunchuk at address 0x");
	Serial.println(NUNCHUK_ADDRESS, HEX);
	if (!Nunchuk.begin(NUNCHUK_ADDRESS))
	{
		Serial.println("******** No nunchuk found");
		Serial.flush();
	}
}
 
void loop()                     
{
  if (Nunchuk.getState(NUNCHUK_ADDRESS))
		{
			if (Nunchuk.state.joy_x_axis== 00)
			{
          if (!algeweest)
          {
            Serial.println("Sending play button");
            SendPlayCode();
            algeweest=true;
            algeweest2 = false;
          }
			} else if (Nunchuk.state.joy_x_axis== 255)
			{
        if (!algeweest2)
        {
          Serial.println("sending linksboven");
          sendlinksboven();
          algeweest2=true;
          algeweest = false;
        }
			}
			else if (Nunchuk.state.joy_y_axis== 255)
			{
        if (!algeweest3)
        {
          Serial.println("sending MiddenBoven");
          sendMiddenBoven();
          algeweest3=true;
          algeweest4 = false;    
        }
			}	
			else if (Nunchuk.state.joy_y_axis== 00)
			{
        if (!algeweest4)
        {
          Serial.println("sending RechtsBoven");
          sendRechtsBoven();
          algeweest4 = true;
          algeweest3 = false;    
        }
			}
		}
}

void pulseIR(long microsecs) {
  
 
  cli();  
 
  if (is38khz)
  {
    while (microsecs > 0) {
    // 38 kHz
    digitalWrite(IRledPin, HIGH);  
    delayMicroseconds(10);         
    digitalWrite(IRledPin, LOW);   
    delayMicroseconds(10);         
 
    // niet aankomen
    microsecs -= 26; 
    }
  } else if (!is38khz) {
      while (microsecs > 0) {
      // 56 kHz 
      digitalWrite(IRledPin, HIGH);  // duurt 3 microseconds
      delayMicroseconds(6);         
      digitalWrite(IRledPin, LOW);   
      delayMicroseconds(6);         
 
      // niet aankomen
      microsecs -= 26;
    }
  }
    sei();  
}
 
void SendPlayCode() {

  // play knop op afstand bedieding
 
  pulseIR(260);
  delayMicroseconds(5504);
  pulseIR(9300);
  delayMicroseconds(4560);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(560);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(620);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1640);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1640);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1640);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(620);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(560);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(620);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(1640);
  pulseIR(640);
  delayMicroseconds(40440);
  pulseIR(9300);
  delayMicroseconds(2260);
  pulseIR(640);
}

void sendlinksboven(){
  pulseIR(260);
  delayMicroseconds(32812);
  pulseIR(9300);
  delayMicroseconds(4560);
  pulseIR(660);
  delayMicroseconds(520);
  pulseIR(660);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(660);
  delayMicroseconds(520);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(660);
  delayMicroseconds(520);
  pulseIR(660);
  delayMicroseconds(520);
  pulseIR(660);
  delayMicroseconds(540);
  pulseIR(660);
  delayMicroseconds(1620);
  pulseIR(660);
  delayMicroseconds(1640);
  pulseIR(620);
  delayMicroseconds(1660);
  pulseIR(660);
  delayMicroseconds(1640);
  pulseIR(660);
  delayMicroseconds(1620);
  pulseIR(660);
  delayMicroseconds(1660);
  pulseIR(600);
  delayMicroseconds(1700);
  pulseIR(620);
  delayMicroseconds(1660);
  pulseIR(620);
  delayMicroseconds(1680);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(620);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(560);
  pulseIR(600);
  delayMicroseconds(580);
  pulseIR(640);
  delayMicroseconds(1640);
  pulseIR(640);
  delayMicroseconds(560);
  pulseIR(600);
  delayMicroseconds(580);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(620);
  delayMicroseconds(1680);
  pulseIR(600);
  delayMicroseconds(1660);
  pulseIR(660);
  delayMicroseconds(1660);
  pulseIR(620);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(1640);
  pulseIR(640);
  delayMicroseconds(40460);
  pulseIR(9260);
  delayMicroseconds(2400);
  pulseIR(480);  
}

void sendMiddenBoven(){
  pulseIR(9340);
  delayMicroseconds(4540);
  pulseIR(660);
  delayMicroseconds(520);
  pulseIR(700);
  delayMicroseconds(480);
  pulseIR(720);
  delayMicroseconds(460);
  pulseIR(680);
  delayMicroseconds(520);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(660);
  delayMicroseconds(520);
  pulseIR(680);
  delayMicroseconds(500);
  pulseIR(660);
  delayMicroseconds(520);
  pulseIR(680);
  delayMicroseconds(1620);
  pulseIR(660);
  delayMicroseconds(1620);
  pulseIR(680);
  delayMicroseconds(1620);
  pulseIR(660);
  delayMicroseconds(1620);
  pulseIR(660);
  delayMicroseconds(1640);
  pulseIR(660);
  delayMicroseconds(1620);
  pulseIR(680);
  delayMicroseconds(1620);
  pulseIR(700);
  delayMicroseconds(1580);
  pulseIR(680);
  delayMicroseconds(520);
  pulseIR(660);
  delayMicroseconds(1620);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(560);
  pulseIR(620);
  delayMicroseconds(1660);
  pulseIR(640);
  delayMicroseconds(1640);
  pulseIR(620);
  delayMicroseconds(1680);
  pulseIR(640);
  delayMicroseconds(540);
  pulseIR(640);
  delayMicroseconds(1660);
  pulseIR(620);
  delayMicroseconds(40480);
  pulseIR(9300);
  delayMicroseconds(2260);
  pulseIR(680);
}

void sendRechtsBoven(){
  pulseIR(9300);
  delayMicroseconds(4600);
  pulseIR(600);
  delayMicroseconds(600);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(600);
  delayMicroseconds(620);
  pulseIR(560);
  delayMicroseconds(600);
  pulseIR(560);
  delayMicroseconds(640);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(600);
  delayMicroseconds(600);
  pulseIR(580);
  delayMicroseconds(620);
  pulseIR(560);
  delayMicroseconds(1720);
  pulseIR(580);
  delayMicroseconds(1680);
  pulseIR(600);
  delayMicroseconds(1720);
  pulseIR(580);
  delayMicroseconds(1700);
  pulseIR(600);
  delayMicroseconds(1700);
  pulseIR(580);
  delayMicroseconds(1700);
  pulseIR(600);
  delayMicroseconds(1720);
  pulseIR(580);
  delayMicroseconds(1680);
  pulseIR(600);
  delayMicroseconds(1720);
  pulseIR(560);
  delayMicroseconds(1760);
  pulseIR(520);
  delayMicroseconds(1720);
  pulseIR(600);
  delayMicroseconds(580);
  pulseIR(600);
  delayMicroseconds(600);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(600);
  delayMicroseconds(1700);
  pulseIR(580);
  delayMicroseconds(600);
  pulseIR(600);
  delayMicroseconds(580);
  pulseIR(600);
  delayMicroseconds(620);
  pulseIR(580);
  delayMicroseconds(580);
  pulseIR(600);
  delayMicroseconds(1700);
  pulseIR(580);
  delayMicroseconds(1700);
  pulseIR(600);
  delayMicroseconds(1720);
  pulseIR(600);
  delayMicroseconds(560);
  pulseIR(600);
  delayMicroseconds(1680);
  pulseIR(600);
  delayMicroseconds(40480);
  pulseIR(9300);
  delayMicroseconds(2300);
  pulseIR(600);
}