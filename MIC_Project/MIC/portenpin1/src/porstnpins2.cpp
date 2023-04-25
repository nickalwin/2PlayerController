#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <HardwareSerial.h>

void Set_leds();
void init_pins();
bool Is_pressed;
char chararray[9] {-4,-3,-2,-1,0,1,2,3,4};

int main(){
    init_pins();
    Is_pressed = false;
    Serial.begin(9600);

    while(true){
        if((PINC & (1<<DDC5)&& !Is_pressed)){
            _delay_ms(50);
            Is_pressed = true;
            Set_leds();// debounce en pas activeren als los laat
        }else if((PINC & (1<<DDC5)) &&Is_pressed){
            Set_leds();
            Is_pressed = false;
        }
    }
}

void Set_leds(){
    //PORTB ^= (1 << PORTB0 | 1 << PORTB1 | 1 << PORTB2 | 1 << PORTB3);
    for (int i = 0; i < 9; i++)
    {
        PORTB = chararray[i];
        _delay_ms(200);
        Serial.println("lamp aan");
    }
}

void init_pins(){
    DDRC = (0 << DDC5);
    PORTC = (1 << PORTC5);
    DDRB = (1 << DDB0 | 1 << DDB1 | 1 << DDB2 | 1 << DDB3);
}
