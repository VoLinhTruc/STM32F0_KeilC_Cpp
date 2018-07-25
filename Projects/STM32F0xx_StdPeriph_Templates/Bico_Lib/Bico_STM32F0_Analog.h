#ifndef __BICO_STM32F0_ANALOG_H
#define __BICO_STM32F0_ANALOG_H

#include "stm32f0xx.h"
#include "Bico_STM32F0_Gpio.h"

#define AIN10	PC0
#define AIN11	PC1
#define AIN12	PC2
#define AIN13	PC3
#define AIN0	PA0
#define AIN1	PA1
#define AIN2	PA2
#define AIN3	PA3
#define AIN4	PA4
#define AIN5	PA5
#define AIN6	PA6
#define AIN7	PA7
#define AIN14	PC4
#define AIN15	PC5
#define AIN8	PB0
#define AIN9	PB1


uint16_t analogRead(uint8_t pin);


#endif
