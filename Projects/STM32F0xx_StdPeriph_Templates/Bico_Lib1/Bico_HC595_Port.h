#ifndef BICO_HC595_PORT_H_
#define BICO_HC595_PORT_H_

#include "Bico_STM8_Generic.h"
#include "Bico_HC595.h"
#include "Logic_Math.h"

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define MAX_NUM_OF_HC595_BIT (MAX_NUM_OF_HC595_IC*8)

class Bico_HC595_Port: public Bico_HC595
{
  public:
    using Bico_HC595::setup;
    Bico_HC595_Port();
    Bico_HC595_Port(unsigned char num_of_HC595_IC);
    Bico_HC595_Port(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order);
    Bico_HC595_Port(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order, unsigned char num_of_HC595_IC, unsigned char SS_pin);

    void setup(uint8_t* pin_array, uint8_t num_of_bit);
    void writePort(long val);
  
  private:
    uint8_t _pin_array[MAX_NUM_OF_HC595_BIT];
    uint8_t _num_of_bit;
};

#endif
