#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	while(1)
	{
		GPIO_ResetBits(GPIOG, GPIO_Pin_2);
		Delay_ms(500);
		GPIO_SetBits(GPIOG, GPIO_Pin_2);
		Delay_ms(500);
	}               
}
