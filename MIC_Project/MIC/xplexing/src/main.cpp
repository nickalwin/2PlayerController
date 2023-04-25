#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint8_t counter = 0;

void Set_leds();
void init_pins();
void Switch_pins();

int main(){
    init_pins();
    DDRC |= (1 << DDC4);
    DDRC |= (0 << DDC5);
    while(true){
        counter++;
        Set_leds();
        _delay_ms(450);
        Switch_pins();
    }
}

void Set_leds(){
    PORTD = counter;
}

void init_pins(){
    DDRD = (1 << DDD0 | 1 << DDD1 | 1 << DDD2 | 1 << DDD3);
}

void Switch_pins(){
    DDRC ^= (1 << DDC4 | 1 << DDC5);
}
