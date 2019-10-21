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
int obstacleDetectionActive = FALSE;

int main(void)
{
    setup();
    while(1){
        loop();
        //stepperMotorControl(2,1);
        //PORTC = 0b00001111;
    }
}

// runs at startup once
void setup() {
    setupTimers();
    setupPin(3,INPUT);
    DDRC = 0b00001111;
    /*setupPin(4,OUTPUT);
    setupPin(5,OUTPUT);
    setupPin(6,OUTPUT);
    setupPin(7,OUTPUT);*/
    setupPin(8,OUTPUT);
    setupPin(10,OUTPUT);
    setupPin(2,INPUT);
    setupPin(12,OUTPUT);
    setupPin(13,OUTPUT);

    SerialBegin(9600);

    setupEngines();

    // the engines need a voltage kick to get going
    // UNFORTUNATELY THIS PWM *STILL* DOESN'T PLAY NICE WITH THE STEPPER MOTOR. looks like I'm gonna have to do the stepper motor in pwm too.
    //analogueOutput(5,1000);
}

// runs indefinitely
void loop() {
    //digitalOutput(4,digitalInput(2));
    //int currentEngineSpeed = engineSpeed; // DO NOT CHANGE; CHANGE GLOBAL VAR
    //digitalOutput(13,ON);
    if(available()) {
        char test[] = "test";
        char input = receiveData();
        transmitData(input);
        if(input == 'l') {
            //digitalOutput(12,ON);
            stepperMotorControl(3,1);
            //SerialSend("Turning Left");
            //snprintf(test,sizeof(test),"Test %d",tt);
        } else if (input == 'r') {
            //digitalOutput(12,OFF);
            stepperMotorControl(3,0);
            //SerialSend("Turning Right");
        } else if(input == 'f') {
            digitalOutput(10,OFF);
           digitalOutput(8,ON);
           // SerialSend("Moving Forwards");
        } else if(input == 'b') {
          // SerialSend("Moving Backwards");
          digitalOutput(8,OFF);
          digitalOutput(10,ON);

        } else if(input > 47 && input <= 57) {
            // between '0' and '9', 10 different bits for different speeds
            /*char output[32];
            engineSpeed = (input - 48) * 114;
            snprintf(output, sizeof(output), "Motor Speed %d \n", engineSpeed);*/
            int number = input - 48;
            setEngineSpeed(number);
            //SerialSend(output);
        } else if(input == 'X') {
            obstacleDetectionActive = TRUE;
            SerialSend("Obstacle Detection Activated.");
        } else if(input == 'x') {
            obstacleDetectionActive = FALSE;
            SerialSend("Obstacle Detection Disabled.");
        }

        if(obstacleDetectionActive) {
        int obstacle = digitalInput(3); // get obstacle threshold from FPGA.
        if(obstacle) {
            SerialSend("Obstacle Detected! Stopping car");
            // enabling BOTH stopping mechanisms. Disabling transistor & h bridge.
            engineSpeed = 0;
            digitalOutput(10,OFF);
            digitalOutput(8,OFF);
        }
    }
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

