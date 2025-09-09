#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"

int16_t Num = 1;
int16_t Speed;

int main(void)
{
	OLED_Init();
	Timer_Init();
	Encoder_Init();

	OLED_ShowString(1,1,"Speed:");
	

	while(1)
	{
		if(Num ==1) 
		{
			TIM_SetCounter(TIM3, 0);  //貌似编码器上电会出现两个边沿，在循环开始前去除这两个边沿
			Num = 0;
		}
		OLED_ShowSignedNum(1,7,Speed,5);
		
		//OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
	}               
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Speed = Encoder_Get();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
	}
}
