#include "stm32f4xx.h"                  // Device header

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//对时基单元无作用，主要提供外部输入滤波器的采样频率
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;   //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1; //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器的重复计数器，TIM2为通用定时器无该寄存器
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure); //在这里会更新中断置标志位导致上电就进入中断
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//选择通道1
	TIM_ICInitStructure.TIM_ICFilter = 0xF; //滤波器选择
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿触发
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; // 分频器不分频
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // IC1选择TI1FP1
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1); //从模式触发源选择
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset); //选择复位从模式
	
	TIM_Cmd(TIM3, ENABLE);
}

uint32_t IC_GetFreq(void)
{
	return 800000 / (TIM_GetCapture1(TIM3) + 1);
}
