#include "Bico_STM32F0_Analog.h"

uint16_t analogRead(uint8_t pin)
{
  uint32_t analog_channel;
  
  switch(pin)
  {
    case AIN0: {analog_channel = ADC_Channel_0; break;}
    case AIN1: {analog_channel = ADC_Channel_1; break;}
    case AIN2: {analog_channel = ADC_Channel_2; break;}
    case AIN3: {analog_channel = ADC_Channel_3; break;}
    case AIN4: {analog_channel = ADC_Channel_4; break;}
    case AIN5: {analog_channel = ADC_Channel_5; break;}
    case AIN6: {analog_channel = ADC_Channel_6; break;}
    case AIN7: {analog_channel = ADC_Channel_7; break;}
    case AIN8: {analog_channel = ADC_Channel_8; break;}
    case AIN9: {analog_channel = ADC_Channel_9; break;}
    case AIN10: {analog_channel = ADC_Channel_10; break;}
    case AIN11: {analog_channel = ADC_Channel_11; break;}
    case AIN12: {analog_channel = ADC_Channel_12; break;}
    case AIN13: {analog_channel = ADC_Channel_13; break;}
    case AIN14: {analog_channel = ADC_Channel_14; break;}
    case AIN15: {analog_channel = ADC_Channel_15; break;}
  }
  
  ADC_InitTypeDef     ADC_InitStructure;
  GPIO_InitTypeDef    GPIO_InitStructure;
  
  /* GPIOx Periph clock enable */
  RCC_AHBPeriphClockCmd(decodeRCC_AHBPeriph_GPIOx(pin), ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* Configure ADC Channelxx as analog input */
  GPIO_InitStructure.GPIO_Pin = decodePin(pin);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init((GPIO_TypeDef*)decodePort(pin), &GPIO_InitStructure);  

  /* ADCs DeInit */  
  ADC_DeInit(ADC1);
  
  /* Initialize ADC structure */
  ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
  ADC_Init(ADC1, &ADC_InitStructure); 

  /* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(ADC1, analog_channel , ADC_SampleTime_239_5Cycles);

  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
  
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
  /* Wait the ADRDY flag */
  for(long count = 0; count < 500000; count++)
  {
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY))
      break;
  }
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(ADC1);

  for(long count = 0; count < 500000; count++)
  {
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == SET)
      break;
  }

  return ADC_GetConversionValue(ADC1);
}
