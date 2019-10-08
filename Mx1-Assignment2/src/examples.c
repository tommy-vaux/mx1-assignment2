#include <avr/io.h>
#include "basicFunctions.h"

// EXAMPLE: USING SNPRINTF (basically printf without the overhead, works for sending serial data)
void snPrintFExample() {
    int tt = 150;
    char test[128];
    snprintf(test,sizeof(test),"Test %d",tt);
    SerialSend(test);
}

void invertedDigitalInputExample() {
    if(PIND & (1<<PIND2)) {

        // if pin 2 is on
        digitalOutput(4,OFF);
    } else {
        while(!(PIND & (1<<PIND2))) {
            digitalOutput(4,ON);
        }
    }  
}