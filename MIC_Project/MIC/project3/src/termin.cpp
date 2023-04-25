#include <avr/io.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>
#include <util/delay.h>


void Timer_init();
void Pins_init();
void ADC_init();

int main(){
    Pins_init();
    ADC_init();
    Timer_init();
    sei();
    while(true){
    }
}

#define ALLADCPINS ((1 << MUX0) | (1 << MUX1) | (1 << MUX2) | (1 << MUX3))
void ADC_init(void)
{
    ADMUX &= ~ALLADCPINS;                                // input channel port A0
    ADMUX |= (1 << REFS0) | (1<<ADLAR);                      // reference voltage on AVCC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1<<ADIE);    // ADC clock prescaler /128 and interrupt enable
    ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0)); // freerunning
    ADCSRA |= (1 << ADATE);                                  // enable auto trigger
    ADCSRA |= (1 << ADEN);                                   // enable ADC
    ADCSRA |= (1 << ADSC);                                   // start first ADC conversion
}

ISR(ADC_vect){
    OCR0A = ADCH;
}


void Timer_init(){
    // init timer 2
    TCCR0A = 0;
    TCCR0B = 0;
    TCCR0A |= (1<<WGM01) | (1<<COM0A0); 
    TIMSK0 |= (1<<TOIE0);
    TCCR0B |= (1<<CS01) | (1<<CS00);
}

void Pins_init(){
    DDRD |= (1<<DDD6);
}