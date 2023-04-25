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
#include <stddef.h>
#include <string.h>


void rot13(char *str) {
    while (*str != '\0') {
        if ((*str >= 'a' && *str <= 'm') || (*str >= 'A' && *str <= 'M')) {
            *str += 13;
        } else if ((*str >= 'n' && *str <= 'z') || (*str >= 'N' && *str <= 'Z')) {
            *str -= 13;
        }
        str++;
    }
}

char toggle_hoofd_klein(uint8_t letter) {
    // Check of het hoogste bit aan staat om te bepalen of het een hoofdletter is
    if ((letter & 0x80) == 0x80) {
        // Zet het hoogste bit uit om er een kleine letter van te maken
        letter &= ~(0x80);
    } else {
        // Zet het hoogste bit aan om er een hoofdletter van te maken
        letter |= 0x80;
    }
    return letter;
}


        // char str[] = "Hello, world!";
        // printf("Before: %s\n", str);
        // rot13(str);
        // printf("After: %s\n", str);

        // de letter A is 0100 0001 B = 0100 0010
        // de letter a is 0110 0001 b = 0110 0010	


int main(void)
{
    DDRB |= (1 << DDB5);                    // pin 13 output mode
    sei();                                  // counter

    Serial.begin(9600);                     // open serial connection
    //Serial.println("hallo dit is een test om efdrx");                // Say hi
    Serial.println(toggle_hoofd_klein('A'));
    Serial.println(toggle_hoofd_klein('B'));
    Serial.println(toggle_hoofd_klein('C'));

    // endless loop

    Serial.flush();
    return(0);                              // keep compiler satisfied (no warnings)
}