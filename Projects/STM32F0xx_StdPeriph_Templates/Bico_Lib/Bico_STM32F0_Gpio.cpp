#include "Bico_STM32F0_Gpio.h"

GPIO_InitTypeDef GPIO_InitStructure = {
	0,
	GPIO_Mode_IN,
	GPIO_Speed_Level_2,	//default value
	GPIO_OType_PP,		//defaule value
	GPIO_PuPd_NOPULL
};

uint32_t decodePort(uint8_t pin)
{
	if(pin < LSB_PB)
		return GPIOA_BASE;
		
	else if(IS_BETWEEN(B, C))
		return GPIOB_BASE;
		
	else if(IS_BETWEEN(C, D))
		return GPIOC_BASE;
		
	else if(IS_BETWEEN(D, E))
		return GPIOD_BASE;

	else if(IS_BETWEEN(E, F))
		return GPIOE_BASE;

	else if(pin > LSB_PF)
		return GPIOF_BASE;
    else return 0;
}

uint16_t decodePin(uint8_t pin)
{
	if(pin < LSB_PB)
		return (1 << (pin - LSB_PA));
		
	else if(IS_BETWEEN(B, C))
		return (1 << (pin - LSB_PB));
		
	else if(IS_BETWEEN(C, D))
		return (1 << (pin - LSB_PC));
		
	else if(IS_BETWEEN(D, E))
		return (1 << (pin - LSB_PD));
    
	else if(IS_BETWEEN(E, F))
		return (1 << (pin - LSB_PE));

	else if(pin > LSB_PF)
		return (1 << (pin - LSB_PF));    
        
	else return 0;
}

uint32_t decodeRCC_AHBPeriph_GPIOx(uint8_t pin)
{
	if(decodePort(pin) == GPIOA_BASE)
		return RCC_AHBPeriph_GPIOA;
	else if(decodePort(pin) == GPIOB_BASE)
		return RCC_AHBPeriph_GPIOB;
	else if(decodePort(pin) == GPIOC_BASE)
		return RCC_AHBPeriph_GPIOC;
	else if(decodePort(pin) == GPIOD_BASE)
		return RCC_AHBPeriph_GPIOD;
	else if(decodePort(pin) == GPIOE_BASE)
		return RCC_AHBPeriph_GPIOE;
	else if(decodePort(pin) == GPIOF_BASE)
		return RCC_AHBPeriph_GPIOF;
	else
		return 0;
}

void pinMode(uint8_t pin, uint8_t mode)
{
	GPIO_InitStructure.GPIO_Pin = decodePin(pin);
	switch(mode)
	{
		case OUTPUT_PP /* or OUTPUT */: 
		{
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			break;
		}
		case OUTPUT_OD: 
		{
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
			break;
		}
		case INPUT:
		{
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			break;
		}
		case INPUT_PULLUP:
		{
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
			break;
		}
		case INPUT_PULLDOWN:
		{
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
			break;
		}
		default: break;
	}
	
	RCC_AHBPeriphClockCmd(decodeRCC_AHBPeriph_GPIOx(pin), ENABLE);
	GPIO_Init((GPIO_TypeDef *) decodePort(pin), &GPIO_InitStructure);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  	GPIO_WriteBit((GPIO_TypeDef*) decodePort(pin), decodePin(pin), (BitAction)val);
}

void digitalWriteReverse(uint8_t pin)
{
  ((GPIO_TypeDef*)decodePort(pin))->ODR ^= decodePin(pin);
} 

uint8_t digitalRead(uint8_t pin)
{
	return GPIO_ReadInputDataBit((GPIO_TypeDef *) decodePort(pin), decodePin(pin));
}


void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
	uint8_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else	
			digitalWrite(dataPin, !!(val & (1 << (7 - i))));
			
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);		
	}
}
