#include "Arduino.h"
#include "Bico_STM32F0_Gpio.h"
	
void delay()
	{
		for(long count = 0; count < 500000; count++)
		{

		}
	}
	
	
	
void setup()
{
	pinMode(PA4, OUTPUT);
	pinMode(PA5, INPUT_PULLDOWN);
}

void loop()
{
	digitalWrite(PA4, digitalRead(PA5));
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
