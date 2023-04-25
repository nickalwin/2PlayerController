#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

int main()
{
  sei();                    // enable interrupts
  Serial.begin(9600);

  // VOORBEELD
  uint8_t a = 'a';
  Serial.println(char(a));  // cast naar char en druk af
  uint8_t b = a;
  b |= (1 << 1);            // maak letter b van letter a
  b &= ~(1 << 0);
  Serial.println(char(b));
  Serial.flush();

  // Opgave a
  uint8_t n = b;
  // maak van de b een n
  // zet hier je eigen code
  n ^= (1 << 2 | 1 << 3);

  Serial.println(char(n));
  Serial.flush();

  //Opgave b
  uint8_t h = n;
  // maak van de n een h
  // zet hier je eigen code
  h ^= (1 << 1 | 1 << 2);
  Serial.println(char(h));
  Serial.flush();

  while(1) ;
}
