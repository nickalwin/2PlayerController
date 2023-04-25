// keep intellisense satisfied
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

uint8_t counter = 0;

enum bstate { pressed, released };
enum bstate lastpressed = released;

void init_pins(){
    DDRC |= (1 << DDC0 | 1 << DDC1 | 1 << DDC2 | 1 << DDC3); // pin A0 t/m A3 naar output zetten.
    DDRD |= (0 << DDD2);
    PORTD |= (1 << PORTD2);
}


void display_counter(uint8_t counter){
    PORTC = counter;
}

bool vehicle_passed(void){
    if (lastpressed == pressed)
    {
        counter++;
        return true;
    }
    return false;
}

enum bstate button_state(void){
    if((PINC & (1<<DDC1)&& !lastpressed)){
        _delay_ms(100);
        lastpressed == true;// debounce en pas activeren als los laat
        Serial.println("pressed");
    }else if((PINC & (1<<DDC1)) &&lastpressed){
        if (vehicle_passed()) {
        display_counter(counter);
        lastpressed == false;  
    }
        Serial.println("released");
    }
}

int main(void)
{ 
    // 1 malig uitvoeren
    // inilatisatie voor ouput pinnen.
    init_pins();
    Serial.begin(9600);
    
    while (1)
    {
        button_state();
    }
    Serial.flush();
} 
