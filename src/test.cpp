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

volatile uint16_t highCounter = 0;
volatile uint16_t lowCounter = 0;
volatile uint32_t counter = 0;
volatile uint32_t bitarraycounter = 0;
volatile boolean fullbit = false;
volatile boolean validbit = false;
int pulsearray[38];
int bitarray[32];

void convertArray();
void printbit();

// Interrupt Service Routine for external interrupt 0 (rising and falling edges)
ISR(INT0_vect)
{
    if (PIND & (1 << PD2))
    {   if(TCNT1 > 2000){
            bitarraycounter = 0;
        }
        pulsearray[bitarraycounter] = TCNT1;
        bitarraycounter++;
        TCNT1 = 0;
        if (bitarraycounter == 35)
        {
            fullbit = true;
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

    // Enable global interrupts
    sei();

    // Main program loop
    while (1)
    {
        convertArray();
        printbit();
    }

    return 0;
}


void convertArray(){
    if (fullbit)
    {
        for (uint16_t i = 0; i < (sizeof(pulsearray)/2); i++)
        {
            if (pulsearray[i] >= 12 && pulsearray[i] <= 23)
            {
                bitarray[i] = 0;
            }   else if(pulsearray[i] >= 29 && pulsearray[i] <= 40)
            {
                bitarray[i] = 1;
            }
            pulsearray[i] = 0;
        }
        if ((sizeof(bitarray)/2) == 32)
        {
            validbit = true;
        }
    }
}

void printbit(){
    if (validbit)
    {    
        for (uint16_t i = 0; i < (sizeof(bitarray)/2); i++)
        {
            Serial.print(bitarray[i]);
            Serial.print(',');
        }
        Serial.println();

        validbit = false;
        fullbit = false;
    }   
}