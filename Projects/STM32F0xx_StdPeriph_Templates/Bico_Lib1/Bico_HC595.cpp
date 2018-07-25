#include "Bico_HC595.h"

unsigned long global_bits_state = 0;

Bico_HC595::Bico_HC595()
{
  _data_pin = MOSI_PIN;
  _clock_pin = CLOCK_PIN;
  _bit_order = MSBFIRST;
  _num_of_HC595_IC = MAX_NUM_OF_HC595_IC;
  _SS_pin = DEFAULT_SS_PIN_HC595;
  _bits_state = 0;
}

Bico_HC595::Bico_HC595(unsigned char num_of_HC595_IC)
{
  _data_pin = MOSI_PIN;
  _clock_pin = CLOCK_PIN;
  _bit_order = MSBFIRST;
  _num_of_HC595_IC = num_of_HC595_IC;
  _SS_pin = DEFAULT_SS_PIN_HC595;
  _bits_state = 0;
}

Bico_HC595::Bico_HC595(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order)
{
  _data_pin = data_pin;
  _clock_pin = clock_pin;
  _bit_order = bit_order;
  _num_of_HC595_IC = MAX_NUM_OF_HC595_IC;
  _SS_pin = DEFAULT_SS_PIN_HC595;
  _bits_state = 0;
}

Bico_HC595::Bico_HC595(unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order, unsigned char num_of_HC595_IC, unsigned char SS_pin)
{
  _data_pin = data_pin;
  _clock_pin = clock_pin;
  _bit_order = bit_order;
  _num_of_HC595_IC = num_of_HC595_IC;
  _SS_pin = SS_pin;
  _bits_state = 0;
}
//-------------------------------------------------------------------------------------
void Bico_HC595::setup()
{
  pinMode(_data_pin, OUTPUT);
  pinMode(_clock_pin, OUTPUT);
  pinMode(_SS_pin, OUTPUT);
}

void Bico_HC595::write(unsigned char data)
{
  #ifdef SERIAL_DEBUG
  Serial.println(data, BIN);
  #endif
  shiftOut(_data_pin, _clock_pin, MSBFIRST, data);
}


void Bico_HC595::write(unsigned int data)
{
  write((unsigned char)data);
  write((unsigned char)(data >> 8));
}

void Bico_HC595::write(unsigned long data)
{
  write((unsigned int)data);
  write((unsigned int)(data>>16));
}

void Bico_HC595::digitalWrite(unsigned char bit, unsigned char val)
{
  if(val == HIGH)
  {
    ::global_bits_state |= ((unsigned long)(1))<<bit;
  }
  else if(val == LOW)
  {
    ::global_bits_state &= ~(((unsigned long)(1))<<bit);
  }

  ::digitalWrite(_SS_pin, LOW); //:: o day muc dich la su dung ham digitalWrite toan cuc, chu khong phai dung digitalWritecua class Bico_HC595, neu khong co :: thi trinh bien dich se hieu digitalWrite la cua class Bico_HC595
  for(int i = 0; i < _num_of_HC595_IC; i++)
  {
    write((unsigned char)(::global_bits_state >> (NUM_OF_BIT_PER_IC*(_num_of_HC595_IC-1 - i)))); 
  }
  ::digitalWrite(_SS_pin, HIGH); //:: o day muc dich la su dung ham digitalWrite toan cuc, chu khong phai dung digitalWritecua class Bico_HC595, neu khong co :: thi trinh bien dich se hieu digitalWrite la cua class Bico_HC595
}
//-----------------------------------------------------------------------------
unsigned char Bico_HC595::getDataPin()
{
  return _data_pin;
}

unsigned char Bico_HC595::getClockPin()
{
  return _clock_pin;
}

unsigned char Bico_HC595::getBitOrder()
{
  return _bit_order;
}

unsigned char Bico_HC595::getNumOfHC595IC()
{
  return _num_of_HC595_IC;
}

unsigned long Bico_HC595::getBitState()
{
  return _bits_state;
}

unsigned char Bico_HC595::getSSPin()
{
  return _SS_pin;
}
//-----------------------------------------------
void Bico_HC595::setDataPin(unsigned char data_pin)
{
  _data_pin = data_pin;
}

void Bico_HC595::setClockPin(unsigned char clock_pin)
{
  _clock_pin = clock_pin;
}

void Bico_HC595::setBitOrder(unsigned char bit_order)
{
  _bit_order = bit_order;
}

void Bico_HC595::setNumOfHC595IC(unsigned char num_of_HC595_IC)
{
  _num_of_HC595_IC = num_of_HC595_IC;
}

void Bico_HC595::setBitState(unsigned long bits_state)
{
  _bits_state = bits_state;
}

void Bico_HC595::setSSPin(unsigned char SS_pin)
{
  _SS_pin = SS_pin;
}
