#include "Arduino.h"
#include "Bico_STM32F0_Gpio.h"
#include "Bico_STM32F0_Analog.h"

#define STOCK_SIZE 500

uint16_t adc_stock[STOCK_SIZE];
int stock_index = 0;
int sum = 0;
int average = 0;
	
int a = 0;
	
void delay()
	{
		for(long count = 0; count < 500000; count++)
		{

		}
	}
	
	
	
void setup()
{
	pinMode(PA4, OUTPUT);
}

void loop()
{
	sum = sum - adc_stock[stock_index];
	adc_stock[stock_index] = analogRead(PA5);
	sum = sum + adc_stock[stock_index];
	average = sum/STOCK_SIZE;
	stock_index = (stock_index + 1) % STOCK_SIZE;
	
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
