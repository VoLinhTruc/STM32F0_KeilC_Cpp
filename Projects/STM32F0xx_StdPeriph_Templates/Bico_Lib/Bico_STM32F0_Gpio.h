#ifndef __BICO_STM32F0_GPIO_H
#define __BICO_STM32F0_GPIO_H

#include "stm32f0xx.h"

#ifndef HIGH
  #define HIGH 1
#endif

#ifndef LOW
  #define LOW 0
#endif

#ifndef CHANGE
  #define CHANGE 2
#endif

#ifndef RISING
  #define RISING  3
#endif

#ifndef FALLING
  #define FALLING 4
#endif

#ifndef LSBFIRST
#define LSBFIRST 0x80 //0x80 cho phu hop voi thu vien SPI
#endif

#ifndef MSBFIRST
#define MSBFIRST 0x00 //0x00 cho phu hop voi thu vien SPI
#endif

#define PA0	0
#define PA1	1
#define PA2	2
#define PA3	3
#define PA4	4
#define PA5	5
#define PA6	6
#define PA7	7
#define PA8	8
#define PA9	9
#define PA10	10
#define PA11	11
#define PA12	12
#define PA13	13
#define PA14	14
#define PA15	15

#define PB0	16
#define PB1	17
#define PB2	18
#define PB3	19
#define PB4	20
#define PB5	21
#define PB6	22
#define PB7	23
#define PB8	24
#define PB9	25
#define PB10	26
#define PB11	27
#define PB12	28
#define PB13	29
#define PB14	30
#define PB15	31

#define PC0	32
#define PC1	33
#define PC2	34
#define PC3	35
#define PC4	36
#define PC5	37
#define PC6	38
#define PC7	39
#define PC8	40
#define PC9	41
#define PC10	42
#define PC11	43
#define PC12	44
#define PC13	45
#define PC14	46
#define PC15	47

#define PD0	48
#define PD1	49
#define PD2	50
#define PD3	51
#define PD4	52
#define PD5	53
#define PD6	54
#define PD7	55
#define PD8	56
#define PD9	57
#define PD10	58
#define PD11	59
#define PD12	60
#define PD13	61
#define PD14	62
#define PD15	63

#define PE0	64
#define PE1	65
#define PE2	66
#define PE3	67
#define PE4	68
#define PE5	69
#define PE6	70
#define PE7	71
#define PE8	72
#define PE9	73
#define PE10	74
#define PE11	75
#define PE12	76
#define PE13	77
#define PE14	78
#define PE15	79

#define PF0	80
#define PF1	81
#define PF2	82
#define PF3	83
#define PF4	84
#define PF5	85
#define PF6	86
#define PF7	87
#define PF8	88
#define PF9	89
#define PF10	90
#define PF11	91
#define PF12	92
#define PF13	93
#define PF14	94
#define PF15	95

#define LSB_PA 0 
#define LSB_PB 16 
#define LSB_PC 32 
#define LSB_PD 48 
#define LSB_PE 64
#define LSB_PF 80 


#define IS_BETWEEN(p1, p2) (pin >= LSB_P##p1)&&(pin < LSB_P##p2)

#define OUTPUT 1			//arduino standard
#define OUTPUT_PP 1
#define OUTPUT_OD 4
#define INPUT 0				//arduino standard
#define INPUT_PULLUP 2		//arduino standard
#define INPUT_PULLDOWN 3

extern GPIO_InitTypeDef GPIO_InitStructure;

uint32_t decodePort(uint8_t pin);
uint16_t decodePin(uint8_t pin);
uint32_t decodeRCC_AHBPeriph_GPIOx(uint8_t pin);

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
void digitalWriteReverse(uint8_t pin);
uint8_t digitalRead(uint8_t pin);

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);

#endif
