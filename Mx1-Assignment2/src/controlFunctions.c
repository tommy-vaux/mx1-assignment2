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
// COPIED FROM https://www.electroschematics.com/avr-pwm/. 
// The only thing I don't get is how to move the output to a different pin.
void setupEngines() {
     DDRB |= (1 << DDB1);
   // PB1 as output (we want engines to be off by default)
   OCR1A = 0;
   // set PWM for 50% duty cycle at 10bit
   TCCR1A |= (1 << COM1A1);
   // set non-inverting mode
   TCCR1A |= (1 << WGM11) | (1 << WGM10);
   // set 10bit phase corrected PWM Mode
   TCCR1B |= (1 << CS11);
   // set prescaler to 8 and starts PWM
}

void setEngineSpeed(int speed) {
    // speed is from 0 to 9
    OCR1A = speed * 113;
}

void stepperMotorControl(int delay, int direction) {

    if(direction) {
        PORTC = 0b00000001;
        delay_ms(delay);
        PORTC = 0b00000010;
        delay_ms(delay);
        PORTC = 0b00000100;
        delay_ms(delay);
        PORTC = 0b00001000;
        delay_ms(delay);
    } else {
        PORTC = 0b00001000;
        delay_ms(delay);
        PORTC = 0b00000100;
        delay_ms(delay);
        PORTC = 0b00000010;
        delay_ms(delay);
        PORTC = 0b00000001;
        delay_ms(delay);
    }
    
}

void motorDirection(int direction) {
    if(direction) {
        digitalOutput(4,ON);
        digitalOutput(7,OFF);
    } else {
        digitalOutput(4,OFF);
        digitalOutput(7,ON);
    }
}