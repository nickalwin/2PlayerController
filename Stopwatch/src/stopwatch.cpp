#include <avr/io.h>
#include <util/delay.h>

const unsigned char SLAVE_ADDRESS = 0x42;
void init_twi();
void send_slave(unsigned char data);
void stop();

int main()
{
    init_twi();
    send_slave(SLAVE_ADDRESS);
    send_slave(0xA4); // willekeurig data. je hoef deze niet te gebruiken
    // send_slave(0b00000011);

    stop();
    return 0;
}

void init_twi() // intialiseren van registers van TWI of(I2C)
{
    TWCR = (1<<TWEN);// het aanzetten van TWI module
    TWSR = 0x00; // configureren  van prescaler
    TWBR = 255;// configureren van de clock tussen de master en de slave
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0); // Use '&' instead of '=='
}

void send_slave(unsigned char data) // data verzenden via TWDR register
{
    TWDR = data;
    TWCR = (1<<TWINT ) | (1<<TWEN);
    while((TWCR & (1<<TWINT)) == 0); // Use '&' instead of '=='
}

void stop() // stop met verzenden
{
    TWCR = (1<<TWINT) | (1<< TWEN) | (1<<TWSTO);
}