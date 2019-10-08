#include <avr/io.h>
#include <string.h>
#include "bluetooth.h"
// this is pretty much entirely based on the code examples in the datasheet.

//#define UBRR CLOCKSPEED/16/BAUD-1 // UBRR is the value that actually sets the baud rate

void SerialBegin(int baud) {
    // calc baud rate
    int ubrr = CLOCKSPEED/16/baud-1;
    // Set baud rate
    UBRR0H = (unsigned char) (ubrr>>8);
    UBRR0L = (unsigned char) ubrr;

    //setup receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    //set data format (frame format): 8 data, 2 stop bits
    UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}
// public
void SerialSend(unsigned char data[MAX_STRING_LENGTH]) { // send from arduino
    for(int i = 0; i < strlen(data); i++) {
        transmitData(data[i]);
    }
}
// private
void transmitData(unsigned char data) {
    // wait until next empty transmit buffer
    while ( !( UCSR0A & (1<<UDRE0)))
    ;
    // put data into buffer for transmission
    UDR0 = data;

}
// private
unsigned char receiveData() {
    // wait to recieve data
    while ( !(UCSR0A & (1<<RXC0)))
    ;
    // return data recieved from buffer (from transmission)
    return UDR0;
}
