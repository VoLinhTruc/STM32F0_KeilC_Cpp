#include "Arduino.h"
#include "Bico_STM32F0_SPI1.h"

uint8_t c = 10;

void setup()
{
	SPI.begin();
	Serial.begin(57600);
	
	pinMode(PA3, OUTPUT);
	digitalWrite(PA3, HIGH);
}

void loop()
{
	digitalWrite(PA3, LOW);
	
	SPI.beginTransaction();
	Serial.println(SPI.transfer(c++));
	SPI.endTransaction();
	
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
