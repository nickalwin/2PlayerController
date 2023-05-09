#include <avr/io.h>
#include <util/delay.h>

#define IR_LED_PIN 3

void sendIRByte(uint8_t byteToSend) {
  // Begin met het sturen van een startbit (LOW)
  PORTD &= ~(1 << IR_LED_PIN);
  _delay_us(2000);

  // Verzend elk bit in byteToSend, beginnend met het meest significante bit
  for (int bit = 7; bit >= 0; bit--) {
    if (byteToSend & (1 << bit)) {
      PORTD |= (1 << IR_LED_PIN); // Stuur een HIGH bit
    } else {
      PORTD &= ~(1 << IR_LED_PIN); // Stuur een LOW bit
    }
    _delay_us(1000);
  }

  // Sluit de byte af met een stopbit (HIGH)
  PORTD |= (1 << IR_LED_PIN);
  _delay_us(2000);
}

int main() {
  DDRD |= (1 << IR_LED_PIN); // Zet de IR LED pin als uitgang
  uint8_t byteToSend = 0b01010101; // Byte om te verzenden
  sendIRByte(byteToSend);
  return 0;
}

