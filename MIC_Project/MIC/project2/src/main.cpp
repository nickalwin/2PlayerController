#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>
#define SECOND 15624;

const unsigned char SLAVE_ADDRESS = 0x42;
const uint8_t sizearray = 16;
int numbarray[sizearray] {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0b10001000,0b10000011,0b11000110,0b10100001,0b10000110,0b10001110}; //todo: laaste letters naar hex zetten
bool Is_pressed = false;
bool timer_is_on = false;
uint8_t counter = 0;



void init_twi();
void init_timer_debounce();
void init_timer_centibeat();
void send_slave(unsigned char data);
void stop();
void init_pins();

int main()
{
    init_twi();
    send_slave(SLAVE_ADDRESS);
    send_slave(0xC0);
    while (1)
    {

    }
    stop();
    return 0;
}

void init_twi() // intialiseren van registers van TWI of(I2C)
{
    TWCR = (1<<TWEN);// het aanzetten van TWI module
    TWSR = 0x00; // configureren  van prescaler
    TWBR = 255;// configureren van de clock tussen de master en de slave
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0);
    init_pins();  
    init_timer_debounce();
    init_timer_centibeat();
}

void send_slave(unsigned char data) // data verzenden via TWDR register
{
    TWDR = data;
    TWCR = (1<<TWINT ) | (1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0); // Use '&' instead of '=='
}

void init_timer_debounce(){
    TCCR0B &= ~((1 << CS02) | (1 << CS00) | (1 << CS01)); // prescaler van de timer uitzetten
    TIMSK0 |= (1 << TOIE0); // enable overflow interrupt
    TCNT0 = 0;
    
}

void init_timer_centibeat(){
    TCCR1A =0;
    TCCR1B &= ~(1<<CS12) | (1<<CS11) | (1<<CS10);
    TCCR1C = 0;
    OCR1A = SECOND;
    TCNT1 = 0;
    TIMSK1 |= (1 <<OCIE1A);
}

void stop() // stop met verzenden
{
    TWCR = (1<<TWINT) | (1<< TWEN) | (1<<TWSTO);
}

void init_pins(){
     DDRD = (0 << DDD2); // zet knop pin naar input
     PORTD = (1 << PORTD2); // zet internal pullup resistor op PC1
     // enable interrupt on button A1
     EIMSK |= (1 << INT0); // activeer bit 0 in het EIMSK register
     EICRA |= (1 << ISC00); // als hij iets op de knop dertecteerd doet hij iets
     sei(); // enable global interrupts    
}

// all interrupts below this line
// ---------------------------------------------------------------------------------------

ISR(INT0_vect){ // interrupt button
    if (Is_pressed)
    {
        if (timer_is_on)
        {
            Is_pressed = false;
            timer_is_on = false; 
            if (Is_pressed = false)
            {
                
                TCCR0B |= (1 << CS02) | (1 << CS00); // timer 0 aanzetten
            }
        } 
        TCCR1B &= ~(1<<CS12) | (1<<CS11) | (1<<CS10); // dit is bij het loslaten van de knop
        counter = 0;                         // timer 1 uitzetten
    } else {
        TCCR0B |= (1 << CS02) | (1 << CS00); // 1/1024 prescaler aanzetten en timer 0 debounce timer
    }
}

ISR(TIMER0_OVF_vect){ // interrupt timer 0 debounce timer
    TCCR0B &= ~((1 << CS02) | (1 << CS00) | (1 << CS01));
    EIMSK &= ~((1 << INT0)); // deactiveerde de knop
    Is_pressed = true;
    TCCR1B |= (1<<CS12); // timer 1 aanzetten
    timer_is_on = true;
    EIMSK |= (1 << INT0); // activeer knop 
}

ISR(TIMER1_COMPA_vect){
    counter++;
    send_slave(numbarray[counter]);
    if (counter>sizearray -2)
    {
        counter = 0;
    }
    
}