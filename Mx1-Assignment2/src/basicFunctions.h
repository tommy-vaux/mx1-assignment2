// some core definitions to make the code cleaner

#define TRUE 1
#define FALSE 0

#define ON 1
#define OFF 0

#define OUTPUT 1
#define INPUT 0


// BASIC FUNCTIONS
//setup
void setupPin(int pinNo, int direction);
void setupTimers();
//use
void digitalOutput(int pinNo, int value);
int digitalInput(int pinNo);
void analogueOutput(int pinNo,int value);
int debouncedInput(int pinNo);

unsigned long getTimerValue(int timer);

void delay_ms(int time);
void delay_us(int time);