#include <avr/io.h>
#include "basicFunctions.h"

// PRIVATE FUNCTION DEFINITIONS
int getDirectionPin(int pinNo);
int getOutputPin(int pinNo);
int getInputPin(int pinNo);

//PUBLIC FUNCTIONS

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


// PRIVATE FUNCTIONS (NOT ACCESSIBLE FROM EXTERNAL FUNCTIONS). Incorrect input returns 0
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