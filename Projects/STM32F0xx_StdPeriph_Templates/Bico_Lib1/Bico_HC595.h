#ifndef BICO_HC595_H_
#define BICO_HC595_H_

#include "Bico_STM8_Generic.h"

//#define SERIAL_DEBUG

//#define SIZE_OF_CHAR 1
//#define SIZE_OF_INT 2
//#define SIZE_OF_LONG 4

#define MOSI_PIN 11
#define CLOCK_PIN 13

#define MAX_NUM_OF_HC595_IC 4
#define NUM_OF_BIT_PER_IC 8 //Always is 8

#define DEFAULT_SS_PIN_HC595 10

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

extern unsigned long global_bits_state;

class Bico_HC595
{
  public:
    Bico_HC595();
    Bico_HC595(unsigned char num_of_HC595_IC);
    Bico_HC595(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order);
    Bico_HC595(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order, unsigned char num_of_HC595_IC, unsigned char SS_pin);

    void setup();
    void write(unsigned char data);
    void write(unsigned int data);
    void write(unsigned long data);
    void digitalWrite(unsigned char bit, unsigned char val);

    unsigned char getDataPin();
    unsigned char getClockPin();
    unsigned char getBitOrder();
    unsigned char getNumOfHC595IC();
    unsigned long getBitState();
    unsigned char getSSPin();
    
    

    void setDataPin(unsigned char data_pin);
    void setClockPin(unsigned char clock_pin);
    void setBitOrder(unsigned char bit_order);
    void setNumOfHC595IC(unsigned char num_of_HC595_IC);
    void setBitState(unsigned long bits_state);
    void setSSPin(unsigned char SS_pin);
    
  protected:
    unsigned char _data_pin;
    unsigned char _clock_pin;
    unsigned char _bit_order;
    unsigned char _num_of_HC595_IC;
    unsigned long _bits_state;
    unsigned char _SS_pin;
};

#endif
