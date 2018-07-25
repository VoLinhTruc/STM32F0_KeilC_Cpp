#include "Bico_Led7Seg_HC595.h"

uint8_t Bico_Led7Seg_HC595::Bico_seg7_anode_code_hc595[16] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};

Bico_Led7Seg_HC595::Bico_Led7Seg_HC595()
{
  _led_type = COMMON_ANODE;
  _num_of_digit = 8;
  _on_delay = DEFAULT_ON_DELAY;
  _off_delay = DEFAULT_OFF_DELAY;
}

Bico_Led7Seg_HC595::Bico_Led7Seg_HC595(uint8_t led_type, uint8_t num_of_digit, int on_delay, int off_delay, unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order, unsigned char SS_pin)
{
  _led_type = led_type;
  if(num_of_digit <= HC_595_MAX_NUM_OF_LED)
  {
    _num_of_digit = num_of_digit;
  }
  else
  {
    _num_of_digit = HC_595_MAX_NUM_OF_LED;
  }
  _on_delay = on_delay;
  _off_delay = off_delay;

  _digit_port.setDataPin(data_pin);
  _digit_port.setClockPin(clock_pin);
  _digit_port.setBitOrder(bit_order);
  _digit_port.setSSPin(SS_pin);
  _code_port.setDataPin(data_pin);
  _code_port.setClockPin(clock_pin);
  _code_port.setBitOrder(bit_order);
  _code_port.setSSPin(SS_pin);
}

//----------------------------------------------------------------------------------------------------------------

void Bico_Led7Seg_HC595::setup(uint8_t* digit, uint8_t* code)
{
  _digit_port.setup(digit, _num_of_digit);
  _code_port.setup(code, 8); //so 8 gom 7 doan tren led va dau .
  for(uint8_t i = 0; i < _num_of_digit; i++)
  {
    clear(i);
  }
}

void Bico_Led7Seg_HC595::setDigit(uint8_t stand, uint8_t val, bool set_point)
{
  if(set_point)
  {
    if(_led_type == COMMON_ANODE)
    {
      _output_data[stand] = Bico_seg7_anode_code_hc595[val] & ANODE_FLOAT_POINT_SYMBOL;
    }
    if(_led_type == COMMON_CATHODE)
    {
      _output_data[stand] = ~(Bico_seg7_anode_code_hc595[val] & ANODE_FLOAT_POINT_SYMBOL);
    }
  }
  else
  {
    if(_led_type == COMMON_ANODE)
    {
      _output_data[stand] = Bico_seg7_anode_code_hc595[val];
    }
    if(_led_type == COMMON_CATHODE)
    {
      _output_data[stand] = ~(Bico_seg7_anode_code_hc595[val]);
    }
  }
}

void Bico_Led7Seg_HC595::setSymbol(uint8_t stand, char symbol)
{
    if(_led_type == COMMON_ANODE)
    {
      switch(symbol)
      {
        case '-': {_output_data[stand] = ANODE_MINUS_SYMBOL; break;}
        case '.': {_output_data[stand] &= ANODE_FLOAT_POINT_SYMBOL; break;}
      }
    }
    if(_led_type == COMMON_CATHODE)
    {
      switch(symbol)
      {
        case '-': {_output_data[stand] = ~ANODE_MINUS_SYMBOL; break;}
        case '.': {_output_data[stand] |= ANODE_FLOAT_POINT_SYMBOL; break;}
      }
    }
}

void Bico_Led7Seg_HC595::clear(uint8_t stand)
{
    if(_led_type == COMMON_ANODE)
    {
      _output_data[stand] = ANODE_NULL_SYMBOL;
    }
    if(_led_type == COMMON_CATHODE)
    {
      _output_data[stand] = ~ANODE_NULL_SYMBOL;
    }
}

void Bico_Led7Seg_HC595::setNumber(signed long num)
{
  seperateDigit(num, _output_data, _num_of_digit);
  for(uint8_t i = 0; i < _num_of_digit; i++)
  {
    if((i >= getNumberOfDigit(num)) && (_output_data[i] == 0))
    {
      if(_led_type == COMMON_ANODE)
      {
        _output_data[i] = ANODE_NULL_SYMBOL;
      }
      if(_led_type == COMMON_CATHODE)
      {
        _output_data[i] = ~ANODE_NULL_SYMBOL;
      }
    }
    else
    {
      if(_led_type == COMMON_ANODE)
      {
        _output_data[i] = Bico_seg7_anode_code_hc595[_output_data[i]];
      }
      if(_led_type == COMMON_CATHODE)
      {
        _output_data[i] = ~Bico_seg7_anode_code_hc595[_output_data[i]];
      }
    }
  }
  if(num < 0)
    {
      setSymbol(getNumberOfDigit(num), '-');
    }
}

void Bico_Led7Seg_HC595::hide()
{
  if(_led_type == COMMON_ANODE)
  {
    _digit_port.writePort(0x00);
  }
  if(_led_type == COMMON_CATHODE)
  {
    _digit_port.writePort(0xFF);
  }
}

void Bico_Led7Seg_HC595::show()
{
  for(uint8_t i = 0; i < _num_of_digit; i++)
  { 
    _code_port.writePort(_output_data[i]);
    // if(_led_type == COMMON_ANODE)
    // {
    //   _digit_port.writePort((uint8_t)(1<<i));
    // }
    // if(_led_type == COMMON_CATHODE)
    // {
    //   _digit_port.writePort((uint8_t)(~(1<<i)));
    // }

    // delayMicroseconds(_on_delay);
    // hide();
    // delayMicroseconds(_off_delay);
  }
}

void Bico_Led7Seg_HC595::setNumberAndShow(signed long val)
{
  setNumber(val);
  show();
}

void Bico_Led7Seg_HC595::brightness(int on_delay, int off_delay)
{
  _on_delay = on_delay;
  _off_delay = off_delay;
}

//--------------------------------------------------------------------------------------

void Bico_Led7Seg_HC595::setLedType(uint8_t led_type)
{
  if((led_type == COMMON_ANODE) || (led_type == COMMON_CATHODE))
  {
    _led_type = led_type;
  }
}

void Bico_Led7Seg_HC595::setNumOfLed(uint8_t num_of_led)
{
  if(num_of_led <= HC_595_MAX_NUM_OF_LED)
  {
    _num_of_digit = num_of_led;
  }
}

void Bico_Led7Seg_HC595::setOnDelay(int on_delay)
{
  _on_delay = on_delay;
}

void Bico_Led7Seg_HC595::setOffDelay(int off_delay)
{
  _off_delay = off_delay;
}

uint8_t Bico_Led7Seg_HC595::getLedType()
{
  return _led_type;
}

uint8_t Bico_Led7Seg_HC595::getNumOfLed()
{
  return _num_of_digit;
}

int Bico_Led7Seg_HC595::getOnDelay()
{
  return _on_delay;
}

int Bico_Led7Seg_HC595::getOffDelay()
{
  return _off_delay;
}

//------------------------------------------------------------------------------------------------
