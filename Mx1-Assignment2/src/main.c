#include <avr/io.h>
#include <avr/interrupt.h>
#include "basicFunctions.h"
#include "bluetooth.h"
#include <string.h>
//#include <avr/delay.h>
#include <stdint.h>
#include "controlFunctions.h"

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
    setupTimers();

    setupPin(4,OUTPUT);
    setupPin(5,OUTPUT);
    setupPin(6,OUTPUT);
    setupPin(2,INPUT);

    SerialBegin(9600);
}

// runs indefinitely
void loop() {
    //digitalOutput(4,digitalInput(2));

    // MAX SPEED - 2 milliseconds (takes about 4 seconds for a full revolution)
    stepperMotorControl(2,1);
    //motorDirection(1);
    motorDirection(1);
    digitalOutput(6,1);
    /*digitalOutput(4,ON);
    delay_ms(1000);
    digitalOutput(4,OFF);
    delay_ms(1000);*/

    /*char test[128];
    snprintf(test,sizeof(test),"The Counter Value is %lu \n",getTimerValue(0));
    SerialSend(test);*/
    
}

