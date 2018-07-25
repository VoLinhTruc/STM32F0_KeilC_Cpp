#include "Bico_HC595_Port.h"

Bico_HC595_Port::Bico_HC595_Port()
{
  Bico_HC595();
}

Bico_HC595_Port::Bico_HC595_Port(unsigned char num_of_HC595_IC)
{
  _data_pin = MOSI_PIN;
  _clock_pin = CLOCK_PIN;
  _bit_order = MSBFIRST;
  _num_of_HC595_IC = num_of_HC595_IC;
  _bits_state = 0;
}

Bico_HC595_Port::Bico_HC595_Port(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order)
{
  Bico_HC595(data_pin, clock_pin, bit_order);
}

Bico_HC595_Port::Bico_HC595_Port(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order, unsigned char num_of_HC595_IC, unsigned char SS_pin)
{
  Bico_HC595(data_pin, clock_pin, bit_order, num_of_HC595_IC, SS_pin);
}

void Bico_HC595_Port::setup(uint8_t* pin_array, uint8_t num_of_bit)
{
  for(uint8_t i = 0; i < num_of_bit; i++)
  {
    if(num_of_bit <= MAX_NUM_OF_HC595_BIT)
    {
      _num_of_bit = num_of_bit;
    }
    else _num_of_bit = MAX_NUM_OF_HC595_BIT;
    _pin_array[i] = pin_array[i];
  }

  setup();
}

void Bico_HC595_Port::writePort(long val)
{
  for(uint8_t i = 0; i < _num_of_bit; i++)
  {
    digitalWrite(_pin_array[i], getBit(val, i));
  }
}

