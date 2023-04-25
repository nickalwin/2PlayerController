/*
 * small blink program
 */
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= (1<<DDB5);		// pin 13 output

    while(1)			// endless loop
    {
        PORTB ^= (1<<PORTB5);	// toggle pin poort 13 buildin-led is poortB5
        _delay_ms(1000);		// wait a while
    }
}