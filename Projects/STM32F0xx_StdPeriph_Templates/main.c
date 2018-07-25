#include "main.h"
class Blink
{
	public:
		Blink();
		void onLed();
		void offLed();
		void delay();
	
	private:
		static long delay_time;
};
Blink::Blink()
{

};

void Blink::onLed()
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET);
	}
	
void Blink::offLed()
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET);
	}

void Blink::delay()
	{
		for(long count = 0; count < delay_time; count++)
		{

		}
	}
long Blink::delay_time = 1000000;

Blink blinker;
	
GPIO_InitTypeDef        GPIO_InitStructure;
	
int main(void)
{

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Infinite loop */
  while (1)
  {
		blinker.onLed();
		blinker.delay();
		blinker.offLed();
		blinker.delay();
  }
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
