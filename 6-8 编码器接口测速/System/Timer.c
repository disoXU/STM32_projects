#include "stm32f4xx.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//开启TIM2时钟
	
	TIM_InternalClockConfig(TIM2);//选择内部时钟源
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//对时基单元无作用，主要提供外部输入滤波器的采样频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 2880 - 1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器的重复计数器，TIM2为通用定时器无该寄存器
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);//在这里会更新中断置标志位会导致上电就进入中断
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除更新标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//使能更新中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;//使能TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//抢占优先级、子优先级配置
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);//
}

/*
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
	}
}
*/

