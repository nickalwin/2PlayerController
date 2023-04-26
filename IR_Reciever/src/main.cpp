#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <HardwareSerial.h>

#define RECV_PIN PB2   // Pinnummer aangesloten op de TSOP2238
#define LED_PIN PD6     // Pinnummer aangesloten op de LED

unsigned long irCode = 0;

void setup() {
  DDRD &= ~(1 << RECV_PIN);     // Configureer de pin als input
  DDRD |= (1 << LED_PIN);       // Configureer de pin als output
  PORTD &= ~(1 << LED_PIN);     // Zet de LED uit
  // Configureer de seriële poort
  Serial.begin(9600);
}

int main(void) {
  setup();  // Voer de setup-functie uit

  while (1) {
    if ((PIND & (1 << RECV_PIN)) == 0) {  // Als er een signaal wordt gedetecteerd
      PORTD |= (1 << LED_PIN);            // Schakel de LED in
      _delay_us(250);                     // Wacht 250 us
      if ((PIND & (1 << RECV_PIN)) == 0) { // Controleer of het signaal aanhoudt
        irCode = 0;
        for (int i = 0; i < 8; i++) {   // Lees de 8 bits van het signaal
          _delay_us(1500);               // Wacht 1,5 ms
          if ((PIND & (1 << RECV_PIN)) != 0) {
            irCode |= 1UL << (7 - i);   // Zet de bit op de juiste plaats
          }
          _delay_us(1500);               // Wacht nogmaals 1,5 ms
        }
        Serial.println(irCode);         // Stuur de code over de seriële poort
      }
      PORTD &= ~(1 << LED_PIN);           // Schakel de LED uit
    }
  }

  return 0;
}
