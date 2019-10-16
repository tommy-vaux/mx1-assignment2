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

char numbers[] = {'0','1','2','3','4','5','6','7','8','9'};

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
    setupPin(12,OUTPUT);
    setupPin(13,OUTPUT);

    SerialBegin(9600);

    // the engines need a voltage kick to get going
    // UNFORTUNATELY THIS PWM *STILL* DOESN'T PLAY NICE WITH THE STEPPER MOTOR. looks like I'm gonna have to do the stepper motor in pwm too.
    analogueOutput(5,1000);
}

// runs indefinitely
void loop() {
    //digitalOutput(4,digitalInput(2));
    int currentEngineSpeed = engineSpeed; // DO NOT CHANGE; CHANGE GLOBAL VAR
    
    if(available()) {
        char test[] = "test";
        char input = receiveData();
        transmitData(input);
        if(input == 'l') {
            //digitalOutput(12,ON);
            stepperMotorControl(5,1);
            //SerialSend("Turning Left");
            //snprintf(test,sizeof(test),"Test %d",tt);
        } else if (input == 'r') {
            //digitalOutput(12,OFF);
            stepperMotorControl(5,0);
            //SerialSend("Turning Right");
        } else if(input == 'f') {
            motorDirection(1);
           // SerialSend("Moving Forwards");
        } else if(input == 'b') {
           motorDirection(0);
          // SerialSend("Moving Backwards");
        } else if(input > 47 && input <= 79) {
            // between '0' and 'O', 32 different bits for different speeds
            char output[12];
            currentEngineSpeed = (input - 47) * 32;
            //sprintf(output, sizeof(output), "Motor Speed %d", currentEngineSpeed);
        }
    }

    //motorDirection(1);
    //c(5,1);
    //motorDirection(1);
    //analogueOutput(5,1020);
    //digitalOutput(5,1);
    //currentEngineSpeed = 1000;

    // THIS MUST RUN AT THE END OF ALL CODE
    if(engineSpeed != currentEngineSpeed){
        analogueOutput(5, engineSpeed);
        currentEngineSpeed = engineSpeed;
    }
}

// uses alot of global vars so I've kept it in the main function for now. Still doesn't play well with DC motors at the same time BTW.
void setupSteering() {
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
}

