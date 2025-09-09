#include "stm32f4xx.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	PWM_Init();	
}

void Motor_SetSpeed(int8_t Speed)
{
	 if (Speed > 0)
	 {
		 GPIO_SetBits(GPIOG, GPIO_Pin_7);
		 GPIO_ResetBits(GPIOG, GPIO_Pin_8);
		 PWM_SetCompare1(Speed);
	 }
	 else
	 {
		 GPIO_ResetBits(GPIOG, GPIO_Pin_7);
		 GPIO_SetBits(GPIOG, GPIO_Pin_8);
		 PWM_SetCompare1(-Speed);
	 }
}
