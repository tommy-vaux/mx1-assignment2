#include <avr/io.h>
#include <avr/interrupt.h>
#include "basicFunctions.h"

// constants are defined in basicFunctions.h. Add specific constants here if necessary

// FUNCTION DEFINITIONS

// core
void setup();
void loop();

//


int main(void) {
    setup();
    while(1) {
        loop();
    }
    return 0;
}

// runs at startup once
void setup() {
    setupPin(4,OUTPUT);
    setupPin(5,OUTPUT);
}

// runs indefinitely
void loop() {
    digitalOutput(4,ON);
    digitalOutput(5,ON);
}