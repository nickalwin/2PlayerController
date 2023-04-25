#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    DDRB |= (1 << DDB5);                    // pin 13 output mode
    uint8_t i=0;
    uint8_t q;
    sei();                            // counter

    Serial.begin(9600);                     // open serial connection
    Serial.println("hallo");                // Say hi
    Serial.flush();

    // endless loop

    for (uint8_t c = 'A'; c <= 'Z'; c++){
        char letter = (char)c;
        Serial.println(letter);       // show counter
        Serial.flush();
         // toggle pin
        _delay_ms(1000);  
    }

    return(0);                              // keep compiler satisfied (no warnings)
}