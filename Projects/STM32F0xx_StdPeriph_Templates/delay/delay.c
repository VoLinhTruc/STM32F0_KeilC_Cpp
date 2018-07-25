 /*
 ===============================================================================
							Microsecond delay
 ===============================================================================
 * @date    31-Jan-2016
 * @author  Domen Jurkovic
 
 * initialize library with: delay_us_init();
 * for 8MHz or more	core frequency clock
 
 * This library doesn't generate precise us delay, so be careful - take a few us more/less
 */

/* Includes ------------------------------------------------------------------*/
#include "delay.h"

uint32_t us_multiplier;

// init delay 
void delay_init(void) {
    RCC_ClocksTypeDef RCC_Clocks;
       
    RCC_GetClocksFreq(&RCC_Clocks); // Get system clocks 
    us_multiplier = RCC_Clocks.SYSCLK_Frequency / 1000000; //For 1 us delay, we need to divide with 1M */
}

// delay function: micros >= 1;   
void delay_us(uint32_t micros){
	micros *= us_multiplier;
	micros /= 6;	//viec chia cho 6 nhu the nay chi dua vao thuc te, khong phai duoc tinh toan
	
	for(uint32_t i = 0; i < micros; i++)
	{
		__asm("NOP");
	}
}

void delay_ms(uint16_t millis)
{
	for(uint32_t i = 0; i < millis; i++)
	{
		delay_us(1000);
	}
}
