#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

void Set_leds();
void init_pins();
bool Is_pressed;

int main(){
    init_pins();
    Serial.begin(9600);
    Is_pressed = false;

    while(true){
        if((PINC & (1<<DDC1)&& !Is_pressed)){
            _delay_ms(100);
            Is_pressed = true;
            Set_leds();// debounce en pas activeren als los laat
            Serial.println("pressed");
        }else if((PINC & (1<<DDC1)) &&Is_pressed){
            Set_leds();
            Is_pressed = false;
            Serial.println("released");
        }
    }
}

void Set_leds(){
    PORTB ^= (1 << PORTB0);
}

void init_pins(){
    DDRC = (0 << DDC1);
    PORTC = (1 << PORTC1);
    DDRB = (1 << DDB0);
}
