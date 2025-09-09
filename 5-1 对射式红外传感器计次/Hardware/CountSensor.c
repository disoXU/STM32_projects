#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource8);
	
	EXTI_InitTypeDef EXTI_InitStructue;
	EXTI_InitStructue.EXTI_Line = EXTI_Line8;
	EXTI_InitStructue.EXTI_LineCmd = ENABLE;
	EXTI_InitStructue.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructue.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructue);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//整个工程只配置一次，多处配置需保证相同
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t CountSensor_Get(void)
{
	 return CountSensor_Count;
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line8) == SET)
	{
		Delay_ms(20);											//延时消抖
		while (GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_8) == 0);	//选择上升沿触发，低电平变成高电平会在0附近抖动，抖动消失后才能视为上升沿结束
		Delay_ms(20);
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}
