#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
		
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_10) == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	
	if (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_11) == 0);
		Delay_ms(20);
		KeyNum = 3;
	}
	return KeyNum;
}
