#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <HardwareSerial.h>

#define RECV_PIN PB2   // Pinnummer aangesloten op de TSOP2238
#define LED_PIN PD6     // Pinnummer aangesloten op de LED

void setup() {
  DDRD &= ~(1 << RECV_PIN);  // stel de pin als input in

  // Configureer de seriële poort
  Serial.begin(9600);
}

void receiveIRByte(uint8_t* byteReceived) {
  // Wacht tot de IR-ontvanger een byte ontvangt
  while (!(PIND & (1 << IR_RECEIVER_PIN)));

  // Wacht tot de startbit (LOW) is ontvangen
  _delay_us(2000);

  // Ontvang elk bit in de byte, beginnend met het meest significante bit
  *byteReceived = 0;
  for (int bit = 7; bit >= 0; bit--) {
    // Wacht op de volgende bit
    while (PIND & (1 << IR_RECEIVER_PIN));

    // Wacht op de halve bitduur
    _delay_us(500);

    // Lees de bit en voeg deze toe aan de ontvangen byte
    if (PIND & (1 << IR_RECEIVER_PIN)) {
      *byteReceived |= (1 << bit);
    }

    // Wacht op de resterende tijd van de bitduur
    _delay_us(500);
  }

  // Wacht op de stopbit (HIGH)
  while (PIND & (1 << IR_RECEIVER_PIN));
  _delay_us(2000);
}

int main(void) {
  setup();  // Voer de setup-functie uit

  while (1) {
    uint8_t byteReceived;
    receiveIRByte(&byteReceived);
    Serial.write(receiveIRByte);
  }

  return 0;
}


