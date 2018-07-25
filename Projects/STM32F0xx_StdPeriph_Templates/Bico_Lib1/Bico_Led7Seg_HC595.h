#ifndef BICO_LED7SEG_HC595_H_
#define BICO_LED7SEG_HC595_H_

#include "Bico_STM8_Generic.h"
#include "Bico_HC595_Port.h"
#include "Algebra_Math.h"

#ifndef COMMON_ANODE
#define COMMON_ANODE 1
#endif
#ifndef COMMON_CATHODE
#define COMMON_CATHODE 2
#endif

#define HC_595_MAX_NUM_OF_LED 16

#ifndef DEFAULT_ON_DELAY
#define DEFAULT_ON_DELAY 1000//in microsecond
#endif
#ifndef DEFAULT_OFF_DELAY
#define DEFAULT_OFF_DELAY 0 //in microsecond
#endif

#ifndef ANODE_MINUS_SYMBOL
#define ANODE_MINUS_SYMBOL 0xBF
#endif
#ifndef ANODE_NULL_SYMBOL
#define ANODE_NULL_SYMBOL 0xFF
#endif
#ifndef ANODE_FLOAT_POINT_SYMBOL
#define ANODE_FLOAT_POINT_SYMBOL  0x7F
#endif

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

class Bico_Led7Seg_HC595
{
  public:
    Bico_Led7Seg_HC595();
    Bico_Led7Seg_HC595(uint8_t led_type, uint8_t num_of_digit, int on_delay, int off_delay, unsigned char data_pin, unsigned char clock_pin, unsigned char bit_order, unsigned char SS_pin);
    void setup(uint8_t* digit, uint8_t* code);
    void setDigit(uint8_t stand, uint8_t val, bool set_point);
    void setSymbol(uint8_t stand, char symbol);
    void clear(uint8_t stand);
    void setNumber(signed long num);
    void hide();
    void show();
    void setNumberAndShow(signed long val);
    void brightness(int on_delay, int off_delay);

    void setLedType(uint8_t led_type);
    void setNumOfLed(uint8_t num_of_led);
    void setOnDelay(int on_delay);
    void setOffDelay(int off_delay);
    uint8_t getLedType();
    uint8_t getNumOfLed();
    int getOnDelay();
    int getOffDelay();
    Bico_HC595_Port _digit_port;
    Bico_HC595_Port _code_port;

  private:
    uint8_t _led_type;
    uint8_t _num_of_digit;
    int _on_delay; //in microsecond
    int _off_delay;
    uint8_t _output_data[HC_595_MAX_NUM_OF_LED];
    static uint8_t Bico_seg7_anode_code_hc595[16];
};

#endif
