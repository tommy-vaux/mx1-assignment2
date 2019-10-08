#include <avr/io.h>
#include "basicFunctions.h"

// CONTROL FUNCTIONS TO CONTROL MOTORS, ETC.

void bitBangPWM(int pin, int input) {
    // input is a number between 1 and 1000 and determines output strength
    digitalOutput(pin,1);
    delay_us(input); // 10% duty cycle
    digitalOutput(pin,0);
    delay_us(1000 - input);

}

void stepperMotorControl(int delay, int direction) {

    if(direction) {
        PORTB = 0b00000001;
        delay_ms(delay);
        PORTB = 0b00000010;
        delay_ms(delay);
        PORTB = 0b00000100;
        delay_ms(delay);
        PORTB = 0b00001000;
        delay_ms(delay);
    } else {
        PORTB = 0b00001000;
        delay_ms(delay);
        PORTB = 0b00000100;
        delay_ms(delay);
        PORTB = 0b00000010;
        delay_ms(delay);
        PORTB = 0b00000001;
        delay_ms(delay);
    }
    
}

void motorDirection(int direction) {
    if(direction) {
        digitalOutput(4,ON);
        digitalOutput(5,OFF);
    } else {
        digitalOutput(4,OFF);
        digitalOutput(5,ON);
    }
}