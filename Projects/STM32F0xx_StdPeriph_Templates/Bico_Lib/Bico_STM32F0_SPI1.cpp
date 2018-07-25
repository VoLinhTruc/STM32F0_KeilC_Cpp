#include "Bico_STM32F0_SPI1.h"

SPISettings::SPISettings()
{
	FirstBit = SPI_FirstBit_MSB;

	//In this case is 48Mhz, BaudRate = 1500000
	BaudRatePrescaler = SPI_BaudRatePrescaler_32;

	ClockPolarity = SPI_CPOL_Low;

	ClockPhase = SPI_CPHA_1Edge;
}

SPISettings::SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
{
	switch(clock)
	{
		case (uint32_t)24000000:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_2;
			break;
		}

		case (uint32_t)12000000:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_4;
			break;
		}

		case (uint32_t)6000000:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_8;
			break;
		}

		case (uint32_t)3000000:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_16;
			break;
		}
		
		case (uint32_t)1500000:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_32;
			break;
		}
		
		case (uint32_t)750000:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_64;
			break;
		}
		
		case (uint32_t)375000:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_128;
			break;
		}
		
		case (uint32_t)187500:
		{
			BaudRatePrescaler = SPI_BaudRatePrescaler_256;
			break;
		}
	}

	switch(bitOrder)
	{
		case LSBFIRST:
		{
			FirstBit = SPI_FirstBit_LSB;
			break;
		}

		case MSBFIRST:
		{
			FirstBit = SPI_FirstBit_MSB;
			break;
		}
	}

	switch(dataMode)
	{
		case SPI_MODE0:
		{
			ClockPolarity = SPI_CPOL_Low;
			ClockPhase = SPI_CPHA_1Edge;
			break;
		}

		case SPI_MODE1:
		{
			ClockPolarity = SPI_CPOL_Low;
			ClockPhase = SPI_CPHA_2Edge;
			break;
		}

		case SPI_MODE2:
		{
			ClockPolarity = SPI_CPOL_High;
			ClockPhase = SPI_CPHA_1Edge;
			break;
		}

		case SPI_MODE3:
		{
			ClockPolarity = SPI_CPOL_High;
			ClockPhase = SPI_CPHA_2Edge;
			break;
		}
	}

}

//------------------------------------------------------------

SPIClass::SPIClass()
{

}

void SPIClass::begin()
{
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
}

void SPIClass::beginTransaction(SPISettings settings)
{
  /* SPI configuration -------------------------------------------------------*/
  /* Enable the SPI periph */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  SPI_I2S_DeInit(SPI1);

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = settings.ClockPolarity;
  SPI_InitStructure.SPI_CPHA = settings.ClockPhase;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = settings.BaudRatePrescaler;//PCLK1 = 3Mhz // SPI clock =11.718kbit/s
  SPI_InitStructure.SPI_FirstBit = settings.FirstBit;
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
}

void SPIClass::beginTransaction()
{
  beginTransaction(SPISettings());
}

uint8_t SPIClass::transfer(uint8_t data)
{
	for(long count = 0; count < SPI1_WAITING_TIMEOUT; count++)
	{
		//Serial.println("SPI_I2S_FLAG_TXE");
		if(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE))
			break;
	}

	SPI_SendData8(SPI1, data);

	for(long count = 0; count < SPI1_WAITING_TIMEOUT; count++)
	{
		//Serial.println("SPI_I2S_FLAG_RXNE");
		if(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE))
			break;
	}

	return SPI_ReceiveData8(SPI1);
}

void SPIClass::endTransaction()
{
	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_RXNE);
	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_TXE);
	SPI_I2S_ClearFlag(SPI1, I2S_FLAG_CHSIDE);
	SPI_I2S_ClearFlag(SPI1, I2S_FLAG_UDR);
	SPI_I2S_ClearFlag(SPI1, SPI_FLAG_CRCERR);
	SPI_I2S_ClearFlag(SPI1, SPI_FLAG_MODF);
	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_OVR);
	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_BSY);
	SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_FRE);
}

void SPIClass::end()
{
	SPI_I2S_DeInit(SPI1);
	SPI_Cmd(SPI1, DISABLE);
}

SPIClass SPI;

