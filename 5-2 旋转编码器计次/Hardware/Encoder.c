#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

int16_t Encoder_Count;

void Encoder_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource7);
	
	EXTI_InitTypeDef EXTI_InitStructue;
	EXTI_InitStructue.EXTI_Line = EXTI_Line8 | EXTI_Line7;
	EXTI_InitStructue.EXTI_LineCmd = ENABLE;
	EXTI_InitStructue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructue.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructue);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//整个工程只配置一次，多处配置需保证相同
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//如果使用了不同的中断函数，需要配置别的中断函数，pin8和7共用
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);	
}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0;
	return Temp;
}

void EXTI9_5_IRQHandler()
{
	if (EXTI_GetITStatus(EXTI_Line8) == SET)
	{
		Delay_ms(1);
		if (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8) == 0)
		{
			if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7) == 0)//B相下降沿，A相低电平正转
			{
				Encoder_Count++;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	
	if (EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		Delay_ms(1);
		if (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_7) == 0)
		{			
			if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_8) == 0)//A相下降沿，B相低电平反转
			{
				Encoder_Count--;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}
