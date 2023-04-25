#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Configureer ADC
    ADCSRA |= (1 << ADEN);  // ADC inschakelen
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // ADC klokdivisie op 128
    ADMUX |= (1 << REFS0);  // Externe spanning als referentie
    ADMUX &= ~(1 << ADLAR);  // Rechtvaardige uitlijning van resultaat

    // Configureer poort A0 als analoge ingangspoort
    DDRC &= ~(1 << PC0);  // Poort PC0 als invoer instellen

    while (1) {
        // Start ADC-conversie
        ADCSRA |= (1 << ADSC);

        // Wacht tot de conversie is voltooid
        while (ADCSRA & (1 << ADSC));

        // Lees het ADC-resultaat uit
        uint16_t adc_value = ADC;

        // Bereken de potmeterwaarde op basis van de ADC-waarde
        uint8_t potmeter_value = adc_value >> 2;  // Shift het 10-bits resultaat naar rechts om een 8-bits potmeterwaarde te krijgen

        // Doe iets met de potmeterwaarde, bijvoorbeeld stuur een LED aan
        // Hieronder staat een voorbeeld van hoe je de LED kan aansturen met de potmeterwaarde:

        OCR1A = potmeter_value;

        // if (potmeter_value > 127) {
        //     // Zet de LED aan
        //     PORTB |= (1 << PB1);
        //     _delay_ms(100);
        // } else {
        //     // Zet de LED uit
        //     _delay_ms(100);
        //     PORTB &= ~(1 << PB1);
        // }
    }

    return 0;
}
