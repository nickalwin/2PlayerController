/*
 * blink program with Serial
 */
// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
    #define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <string.h>

#define IR_LED_PIN 6

void sendIRByte(uint8_t byteToSend) {
    // Begin met het sturen van een startbit (LOW)
    PORTD &= ~(1 << IR_LED_PIN);
    _delay_ms(2000);

    // Verzend elk bit in byteToSend, beginnend met het meest significante bit
    for (int bit = 7; bit >= 0; bit--) {
        if (byteToSend & (1 << bit)) {
            PORTD |= (1 << IR_LED_PIN); // Stuur een HIGH bit
        } else {
            PORTD &= ~(1 << IR_LED_PIN); // Stuur een LOW bit
        }
        _delay_ms(1000);
    }

    // Sluit de byte af met een stopbit (HIGH)
    PORTD |= (1 << IR_LED_PIN);
    _delay_ms(2000);
}

void initled(){
    DDRD |= (1 << IR_LED_PIN);
}

void sendIRMessage(char* message) {
  // Verzend elk karakter in het bericht
  for (int i = 0; i < strlen(message); i++) {
    uint8_t asciiCode = message[i]; // Haal de ASCII-code op voor het huidige karakter
    sendIRByte(asciiCode); // Verzend de ASCII-code als een byte
  }
}

int main(int argc, char const *argv[])
{
    initled();

    while (1)
    {
        char* message = "Hello, world!"; // Bericht om te verzenden
        sendIRMessage(message);
        _delay_ms(1000); // Wacht 1 seconde voordat u het bericht opnieuw verzendt 
    }
    
    return 0;
}
