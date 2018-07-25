#ifndef __BICO_STM32F0_SERIAL1_H
#define __BICO_STM32F0_SERIAL1_H

#include "stm32f0xx.h"
#include "Algebra_Math.h"


#define USARTx                           USART1
#define USARTx_CLK                       RCC_APB2Periph_USART1
#define USARTx_APBPERIPHCLOCK            RCC_APB2PeriphClockCmd
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler

#define USARTx_TX_PIN                    GPIO_Pin_9
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define USARTx_TX_SOURCE                 GPIO_PinSource9
#define USARTx_TX_AF                     GPIO_AF_1

#define USARTx_RX_PIN                    GPIO_Pin_10          
#define USARTx_RX_GPIO_PORT              GPIOA            
#define USARTx_RX_GPIO_CLK               RCC_AHBPeriph_GPIOA
#define USARTx_RX_SOURCE                 GPIO_PinSource10
#define USARTx_RX_AF                     GPIO_AF_1


#define UART1_WAITING_TIMEOUT 100000 //in cycle unit
#define SERIAL_RX_BUFFER_SIZE 16
typedef uint8_t rx_buffer_index_t;

class HardwareSerial
{
protected:
	volatile rx_buffer_index_t _rx_buffer_head;
	volatile rx_buffer_index_t _rx_buffer_tail;
	volatile unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
	unsigned int timeout;

public:
	HardwareSerial();

	void begin(uint32_t baud);
	void setTimeout(unsigned long second);
	void isr(char c);
	uint8_t available();
	char read();
	//uint8_t readString();
	void write(char c);
	void write(uint8_t c);
	void println();
	uint8_t print(const char* str);
	uint8_t println(const char* str);
	uint8_t print(char* array, uint8_t length);
	uint8_t println(char* array, uint8_t length);
	void print(char c);
	void println(char c);
	void print(uint8_t c);
	void println(uint8_t c);
	void print(int number);
	void println(int number);
	void print(long number);
	void println(long number);
	//void print(float number, num_of_frac_part);
	//void println(float number, num_of_frac_part);
	//void print(float number);
	//void println(float number);
	//void print(string str);
	//void println(string str);
        int peek(void);
};

extern HardwareSerial Serial;

#endif
