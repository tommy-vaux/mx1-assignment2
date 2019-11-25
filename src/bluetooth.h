
#define CLOCKSPEED 16000000

#define MAX_STRING_LENGTH 127

// setup the serial system
void SerialBegin(int baud);

// send a string over serial
void SerialSend(unsigned char data[MAX_STRING_LENGTH]);

// recieve a char from serial
unsigned char receiveData();
void transmitData(unsigned char data);
int available ();