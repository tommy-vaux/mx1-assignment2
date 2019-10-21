#include <avr/io.h>
#include <avr/interrupt.h>
#include "basicFunctions.h"
#include "bluetooth.h"
#include <avr/delay.h>

// PRIVATE FUNCTION DEFINITIONS
int getDirectionPin(int pinNo);
int getOutputPin(int pinNo);
int getInputPin(int pinNo);
void setupDelay();

unsigned long msTimer = 0;

// Digital button input debouncing system (based on the Arduino example)
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = OFF;
int buttonState;

int lol = 0;

// NOTE - TIMER USES TIMER0, PWM uses TIMER1

// INTERRUPTS
ISR(TIMER0_COMPA_vect) {
    msTimer++;
    TCNT0 = 0;
} // this counts every ms



// *TEMP* SOLUTION AS I JUST CANT GET MY OWN TIMERS WORKING THIS WAY FOR SOME REASON
void delay_ms(int time) {
    for(int i = 0; i < time; i++) {
        _delay_ms(1);
    }
}

void delay_us(int time) {
    for(int i = 0; i < time; i++) {
        _delay_us(1);
    }
}

// max input is about 32000 -> 
/*void delay_us(unsigned int time) {
    unsigned long currentTimer = usTimer;
    while((usTimer - currentTimer) < time) {
        digitalOutput(5,ON);
    }
}
// new idea: implement without while (means you need to use output)
void delay_ms(unsigned int time) {
    
    unsigned long currentTimer = msTimer;
    unsigned long timer = msTimer - currentTimer;
    while((timer) < time){
        timer = usTimer - currentTimer;
        char test[128];
        snprintf(test,sizeof(test),"The Counter Value is %lu \n",timer);
        SerialSend(test);
    }
        
}*/


//PUBLIC FUNCTIONS

void setupTimers() {
    sei();
    setupDelay();
}

unsigned long getTimerValue(int timer) {
    if(timer == 1) {
        return msTimer;
    }
    
}

void setupPin(int pinNo, int direction) {
    int pinID = getDirectionPin(pinNo);
    if(pinNo < 8) {
        if(direction) {
            // OUTPUT
            DDRD |= (1<<pinID);
        } else {
            // INPUT
            DDRD &= ~(1<<pinID);
        }
    } else if (pinNo < 14) {
        if(direction) {
            //output
            DDRB |= (1<<pinID);
        } else {
            //input
            DDRB &= ~(1<<pinID);
        }
    }
}

void digitalOutput(int pinNo, int value) {
    int pinID = getOutputPin(pinNo);
    if(pinNo < 8) {
        // AREA D
        if(value) {
            //On
            PORTD |= (1<<pinID);
        } else {
            //Off
            PORTD &= !(1<<pinID);
        }
    } else if (pinNo < 14) {
        // AREA B
        if(value) {
            //On
            PORTB |= (1<<pinID);
        } else {
            //Off
            PORTB &= !(1<<pinID);
        }
    }
}

int debouncedInput(int pinNo) { // doesn't work; have found the digitalInput is good enough anyway.
    int reading = digitalInput(pinNo);
    int output = FALSE;
    if(reading != lastButtonState) {
        lastDebounceTime = msTimer;
    }
    if((msTimer - lastDebounceTime) > debounceDelay){
        if(reading != buttonState) {
            buttonState = reading;
            if(buttonState == ON) {
                output = TRUE;
            }
        }
    }
    lastButtonState = reading;
    return output;
}

int digitalInput(int pinNo) {
    int output = FALSE;
    int pinID = getInputPin(pinNo);
    if(pinNo < 8) {
        if(PIND & (1<<pinID)) {
            output = TRUE;
        }
        
    } else if (pinNo < 14) {
        if(PINB & (1<<pinID)) {
            output = TRUE;
        }
    }
    return output;
}

int digitalInputInversed(int pinNo) {
    int output = FALSE;
    int pinID = getInputPin(pinNo);
    if(pinNo < 8) {
        if(PIND & (1<<pinID)) {
            output = FALSE;
        } else {
            while(!(PIND & (1<<pinID))) {
                output = TRUE;
            }
        }
        
    } else if (pinNo < 14) {
        if(PINB & (1<<pinID)) {
            output = FALSE;
        } else {
            while(!(PINB & (1<<pinID))) {
                output = TRUE;
            }
        }
    }
    return output;
}

// based off code from https://www.electroschematics.com/avr-pwm/
void analogueOutput(int pinNo, int value) {
    setupPin(pinNo, OUTPUT);
    // set duty cycle. As this is timer 1 and we will be using 10 bit, max range is 1024
    OCR1A = value;
    // set non-inverting mode
    TCCR1A |= (1 << COM1A1);
    // set 10bit phase corrected PWM Mode
    TCCR1A |= (1 << WGM11) | (1 << WGM10);
    // set prescaler to 8 and starts PWM
    TCCR1B |= (1 << CS11);
   

}

// PRIVATE FUNCTIONS (NOT ACCESSIBLE FROM EXTERNAL FUNCTIONS). Incorrect input returns 0
// Timer 0 - us delay seems to have issues.
void setupDelay(){ // sets up timer0 for delay
    TCCR0A = 0b00000000; // everything turned off

    TCNT0 = 0;
    
    OCR0A = 250; // the value to compare the timer to (prescaling for milliseconds), 64*250 = 16000

    TIMSK0 = 0b00000010; // interrupt enabled for compare A

    TCCR0B = 0b00000011; // START TIMER; 64 prescaler

}

#pragma region basicHidden
int getDirectionPin(int pinNo) {
    if(pinNo == 0) {
        return DDD0;
    } else if(pinNo == 1) {
        return DDD1;
    } else if(pinNo == 2) {
        return DDD2;
    } else if(pinNo == 3) {
        return DDD3;
    } else if(pinNo == 4) {
        return DDD4;
    } else if(pinNo == 5) {
        return DDD5;
    } else if(pinNo == 6) {
        return DDD6;
    } else if(pinNo == 7) {
        return DDD7;
    } else if(pinNo == 8) {
        return DDB0;
    } else if(pinNo == 9) {
        return DDB1;
    } else if(pinNo == 10) {
        return DDB2;
    } else if(pinNo == 11) {
        return DDB3;
    } else if(pinNo == 12) {
        return DDB4;
    } else if(pinNo == 13) {
        return DDB5;
    } else {
        return 0;
    }
}

int getOutputPin(int pinNo) {
    //
    if(pinNo == 0) {
        return PORTD0;
    } else if(pinNo == 1) {
        return PORTD1;
    } else if(pinNo == 2) {
        return PORTD2;
    } else if(pinNo == 3) {
        return PORTD3;
    } else if(pinNo == 4) {
        return PORTD4;
    } else if(pinNo == 5) {
        return PORTD5;
    } else if(pinNo == 6) {
        return PORTD6;
    } else if(pinNo == 7) {
        return PORTD7;
    } else if(pinNo == 8) {
        return PORTB0;
    } else if(pinNo == 9) {
        return PORTB1;
    } else if(pinNo == 10) {
        return PORTB2;
    } else if(pinNo == 11) {
        return PORTB3;
    } else if(pinNo == 12) {
        return PORTB4;
    } else if(pinNo == 13) {
        return PORTB5;
    } else {
        return 0;
    }
}

int getInputPin(int pinNo) {
    if(pinNo == 0) {
        return PIND0;
    } else if(pinNo == 1) {
        return PIND1;
    } else if(pinNo == 2) {
        return PIND2;
    } else if(pinNo == 3) {
        return PIND3;
    } else if(pinNo == 4) {
        return PIND4;
    } else if(pinNo == 5) {
        return PIND5;
    } else if(pinNo == 6) {
        return PIND6;
    } else if(pinNo == 7) {
        return PIND7;
    } else if(pinNo == 8) {
        return PINB0;
    } else if(pinNo == 9) {
        return PINB1;
    } else if(pinNo == 10) {
        return PINB2;
    } else if(pinNo == 11) {
        return PINB3;
    } else if(pinNo == 12) {
        return PINB4;
    } else if(pinNo == 13) {
        return PINB5;
    } else {
        return 0;
    }
}
#pragma endregion