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

// GLOBAL VARS
int engineSpeed = 1000;
int steps = 0;
int stepGoal = 0;
int steeringInitialised = FALSE;
int readyToUse = FALSE;

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
    setupPin(13,OUTPUT);

    SerialBegin(9600);

    // the engines need a voltage kick to get going
    // UNFORTUNATELY THIS PWM *STILL* DOESN'T PLAY NICE WITH THE STEPPER MOTOR. looks like I'm gonna have to do the stepper motor in pwm too.
    //analogueOutput(9,1000);
}

// runs indefinitely
void loop() {
    //digitalOutput(4,digitalInput(2));
    int currentEngineSpeed = engineSpeed; // DO NOT CHANGE; CHANGE GLOBAL VAR
    // MAX SPEED - 2 milliseconds (takes about 4 seconds for a full revolution)
    int button = digitalInput(2);
    if(steeringInitialised == FALSE){
        steeringInitialised = !button;
        stepperMotorControl(10,1);
    } else {
        if(!readyToUse) {
            stepGoal = 64; // MOVE BACK TO CENTRE

        }
        if(steps != stepGoal) {
            if(!readyToUse) {
                stepperMotorControl(5,0);
            } else {
                // other steering code (not completed goal)
            }
            steps++;
        } else {
            if(!readyToUse) {
                readyToUse = TRUE;
            } else {
                // other steering code (completed goal)
            }
        }
        
    }
    
    //motorDirection(1);
    //motorDirection(1);
    //digitalOutput(6,1);
    /*digitalOutput(4,ON);
    delay_ms(1000);
    digitalOutput(4,OFF);
    delay_ms(1000);*/
    /*int button = digitalInput(2); // DIGITAL INPUT SEEMS TO BE GOOD ENOUGH WITHOUT THE DEBOUNCER
    if(button) {
        digitalOutput(13,OFF);
        engineSpeed = 1000;

    } else {
        digitalOutput(13,ON);
        engineSpeed = 0;
    }*/
    
    /*if(debouncedInput(2)) {
        engineSpeed = 900;
    } else {
        engineSpeed = 0;
    }*/
    
    
    /*char test[128];
    snprintf(test,sizeof(test),"The Counter Value is %lu \n",getTimerValue(0));
    SerialSend(test);*/

    // THIS MUST RUN AT THE END OF ALL CODE
    if(engineSpeed != currentEngineSpeed){
        analogueOutput(9, engineSpeed);
        currentEngineSpeed = engineSpeed;
    }
}

