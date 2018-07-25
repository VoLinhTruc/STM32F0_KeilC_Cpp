#include "Bico_STM32F0_Serial1.h"


HardwareSerial::HardwareSerial() {};

void HardwareSerial::begin(uint32_t baud)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  USARTx_APBPERIPHCLOCK(USARTx_CLK, ENABLE);
  
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);
  
  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
  GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
  GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

  /* USARTx configuration ----------------------------------------------------*/
  /* USARTx configured as follow:
  - BaudRate = 9600 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = baud;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USARTx, &USART_InitStructure);
  
  /* NVIC configuration */
  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
  USART_Cmd(USARTx, ENABLE);
  
  /* Enable the USARTx Receive interrupt: this interrupt is generated when the
  USARTx receive data register is not empty */
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
}

void HardwareSerial::setTimeout(unsigned long val)
{
  timeout = val;
}

void HardwareSerial::isr(char c)
{
  rx_buffer_index_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
  if (i != _rx_buffer_tail) 
  {
    _rx_buffer[_rx_buffer_head] = c;
    _rx_buffer_head = i;
  }
}

uint8_t HardwareSerial::available()
{
  return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

char HardwareSerial::read()
{
  if (_rx_buffer_head == _rx_buffer_tail) 
  {
    return (char)-1;
  } 
  else 
  {
    unsigned char c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
    return c;
  }
}

void HardwareSerial::write(char c)
{
  USART_SendData(USART1, c);
  for(long count = 0; count < UART1_WAITING_TIMEOUT; count++)
  {
   if(USART_GetFlagStatus(USART1, USART_FLAG_TC))
     break;
  }
}

void HardwareSerial::write(uint8_t c)
{
  write((char)c);
}

void HardwareSerial::println()
{
  print("\r\n");
}

uint8_t HardwareSerial::print(const char* str)
{
  uint8_t i = 0;
  while(str[i] != '\0')
  {
    write(str[i]);
    i++;
  }
  return i;
}

uint8_t HardwareSerial::println(const char* str)
{
  uint8_t origin_str = print(str);
  uint8_t rn_str = print("\r\n");
  return (origin_str + rn_str);
}

uint8_t HardwareSerial::print(char* array, uint8_t length)
{
  for(uint8_t i = 0; i < length; i++)
  {
    write(array[i]);
  }
  
  return length;
}

uint8_t HardwareSerial::println(char* array, uint8_t length)
{
  uint8_t origin_str = print(array, length);
  uint8_t rn_str = print("\r\n");
  return (origin_str + rn_str);
}

void HardwareSerial::print(uint8_t c)
{
  print((long)c);
}

void HardwareSerial::println(uint8_t c)
{
  println((long)c);
}

void HardwareSerial::print(char c)
{
  write(c);
}

void HardwareSerial::println(char c)
{
  write(c);
  println();
}

void HardwareSerial::print(int number)
{
  print((long)number);
}

void HardwareSerial::println(int number)
{
  println((long)number);
}

void HardwareSerial::print(long number)
{
  if(number < 0)
    write('-');
  for(uint8_t i = 0; i < getNumberOfDigit(number); i++)
  {
    uint8_t temp= 48+getDigitInNumber(number, getNumberOfDigit(number)-1 - i);
    write(temp);
  }
}

void HardwareSerial::println(long number)
{
  if(number < 0)
    write('-');
  for(uint8_t i = 0; i < getNumberOfDigit(number); i++)
  {
    uint8_t temp= 48+getDigitInNumber(number, getNumberOfDigit(number)-1 - i);
    write(temp);
  }
  print("\r\n");
}

int HardwareSerial::peek(void)
{
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    return _rx_buffer[_rx_buffer_tail];
  }
}

HardwareSerial Serial;
