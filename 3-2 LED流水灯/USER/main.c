#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	while(1)
	{
		GPIO_Write(GPIOG, ~0x0004); //0000 0000 0100
		Delay_ms(200);
		GPIO_Write(GPIOG, ~0x0008); //0000 0000 1000
		Delay_ms(200);
		GPIO_Write(GPIOG, ~0x0010); //0000 0001 0000
		Delay_ms(200);
		GPIO_Write(GPIOG, ~0x0020); //0000 0010 0000
		Delay_ms(200);
	}               
}
