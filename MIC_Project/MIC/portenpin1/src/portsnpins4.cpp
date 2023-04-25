#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_pins();

int main(int argc, char const *argv[])
{
    init_pins();
    for (int i = 0; i < 200; i++)
    {
        PORTB ^= PORTB;
    }
    
    return 0;
}



void init_pins(){
    DDRB = 0xAA;
}