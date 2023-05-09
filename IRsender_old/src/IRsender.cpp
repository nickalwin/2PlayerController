/*
 * blink program with Serial
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

int main(void)
{
    DDRD |= (1 << DDD6);                    // pin 13 output mode
    uint8_t i=0;                            // counter

    Serial.begin(9600);                     // open serial connection
    Serial.println("hallo");                // Say hi
    Serial.flush();

    // endless loop
    while (1)
    {
            Serial.println(i++, DEC);       // show counter
            Serial.flush();

            PORTD ^= (1<<PORTD6);           // toggle pin
            _delay_ms(1000);                // wait a while
    }

    return(0);                              // keep compiler satisfied (no warnings)
}