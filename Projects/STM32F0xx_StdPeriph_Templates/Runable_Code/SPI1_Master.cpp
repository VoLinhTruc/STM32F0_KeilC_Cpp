#include "Arduino.h"
#define SPI1_WAITING_TIMEOUT 100000
uint8_t c = 10;

void setup()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

  SPI_I2S_DeInit(SPI1);
  /* Enable the SPI periph */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  /* Enable SCK, MOSI, MISO and NSS GPIO clocks */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;//GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI configuration -------------------------------------------------------*/

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//PCLK1 = 3Mhz // SPI clock =11.718kbit/s
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  /* Initializes the SPI communication */
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_Init(SPI1, &SPI_InitStructure);


//  /* Initialize the FIFO threshold */
  SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);

  /* Enable the SPI peripheral */
  SPI_Cmd(SPI1, ENABLE);

  /* Wait busy flag */
	for(long count = 0; count < SPI1_WAITING_TIMEOUT; count++)
  {
		//Serial.println("SPI_I2S_FLAG_RXNE");
   if(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY))
     break;
  }
	
	Serial.begin(57600);
	
	pinMode(PA3, OUTPUT);
	digitalWrite(PA3, HIGH);
}

void loop()
{
	digitalWrite(PA3, LOW);
	for(long count = 0; count < SPI1_WAITING_TIMEOUT; count++)
  {
		//Serial.println("SPI_I2S_FLAG_TXE");
   if(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE))
     break;
  }
	
	SPI_SendData8(SPI1, c++);
	
	for(long count = 0; count < SPI1_WAITING_TIMEOUT; count++)
  {
		//Serial.println("SPI_I2S_FLAG_RXNE");
   if(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
     break;
  }
	
	Serial.write(SPI_ReceiveData8(SPI1));
	digitalWrite(PA3, HIGH);
	
	delay_ms(1000);
}
















#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
