#include "stm32f4xx.h"                  // Device header

void LED_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOG, GPIO_Pin_2 | GPIO_Pin_3);
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_2);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOG, GPIO_Pin_2);
}

void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_2) == 0)
	{
		GPIO_SetBits(GPIOG, GPIO_Pin_2);
	}
	else
	{
		GPIO_ResetBits(GPIOG, GPIO_Pin_2);
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOG, GPIO_Pin_3);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOG, GPIO_Pin_3);
}

void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_3) == 0)
	{
		GPIO_SetBits(GPIOG, GPIO_Pin_3);
	}
	else
	{
		GPIO_ResetBits(GPIOG, GPIO_Pin_3);
	}
}
