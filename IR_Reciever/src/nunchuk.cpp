#include <avr/io.h>
#include <util/delay.h>

#define IR_LED_PIN 3

void sendIRByte(uint8_t byteToSend) {
  // Begin met het sturen van een startbit (LOW)
  PORTD &= ~(1 << IR_LED_PIN); // Set IR_LED_PIN LOW
  _delay_us(2000);

  // Verzend elk bit in byteToSend, beginnend met het meest significante bit
  for (int bit = 7; bit >= 0; bit--) {
    if (byteToSend & (1 << bit)) {
      PORTD |= (1 << IR_LED_PIN); // Set IR_LED_PIN HIGH
    } else {
      PORTD &= ~(1 << IR_LED_PIN); // Set IR_LED_PIN LOW
    }
    _delay_us(1000);
  }

  // Sluit de byte af met een stopbit (HIGH)
  PORTD |= (1 << IR_LED_PIN); // Set IR_LED_PIN HIGH
  _delay_us(2000);
}

int main(int argc, char const *argv[])
{
	DDRD |= (1 << IR_LED_PIN); // Set IR_LED_PIN as OUTPUT

	while (1)
	{
		uint8_t byteToSend = 0x5A; // Hexadecimale waarde om te verzenden
		sendIRByte(byteToSend);
		_delay_ms(1000); // Wacht 1 seconde voordat u de volgende byte verzendt
	}
	
	return 0;
}
