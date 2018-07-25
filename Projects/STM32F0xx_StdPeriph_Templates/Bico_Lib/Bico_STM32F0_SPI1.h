#ifndef __BICO_STM32F0_SPI1_H
#define __BICO_STM32F0_SPI1_H

#include "stm32f0xx.h"
#include "main.h"

#define SPI1_WAITING_TIMEOUT 100000

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define MOSI PA7
#define MISO PA6
#define SCK PA5

class SPISettings 
{
public:
	SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode);
	SPISettings(); //defautl see at ../Arduino/hardware/arduino/avr/libraries/SPI/src/SPI.h

	uint16_t FirstBit;
	uint16_t BaudRatePrescaler;
	uint16_t ClockPolarity;
	uint16_t ClockPhase;
};


class SPIClass {
public:
	SPIClass();
	void begin();
	void beginTransaction(SPISettings settings);
	void beginTransaction();
	uint8_t transfer(uint8_t data);
	//uint16_t transfer16(uint16_t data);
	//void transfer(void *buf, size_t count);
	void endTransaction(void);
	void end();

	//void setBitOrder(uint8_t bitOrder);
	//void setDataMode(uint8_t dataMode);
	//void setClockDivider(uint8_t clockDiv);

private:
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
};

extern SPIClass SPI;

#endif
