#include <stdio.h>
#include <HardwareSerial.h>
#include <util/delay.h>
#include <avr/interrupt.h>

bool isHoofdLetter(char c) {
    return(!c & (1 << 5));
}

bool isKleinLetter(char c){
    return (c & (1 << 5));
}

int whatIsBinary(char c){
    int i;
    for (i = 7; i >= 0; i--) {
        Serial.print((c >> i) & 1);
    }
}

int main(int argc, char const *argv[])
{
    Serial.begin(9600);
    char Char = 'B';
    bool result = false;
    bool result2 = false;
    int resultint =0;

    while (1)
    {
        result2 = isHoofdLetter(Char);
        //result = isKleinLetter(Char);
        _delay_ms(1000);
        Serial.println(result);
        Serial.println(whatIsBinary(Char));
        if (result == false || result2){
           Serial.println("klopt niet");
        } else if (result|| result2 == false) {
            Serial.println("dit klopt");
        }
    }
    Serial.flush();
    return 0;
}
