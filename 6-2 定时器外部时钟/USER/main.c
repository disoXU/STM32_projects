#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int main(void)
{
	OLED_Init();
	Timer_Init();

	OLED_ShowString(1,1,"Num:");
	OLED_ShowString(2,1,"CNT:");
	OLED_ShowString(3,1,"PA5:");

	while(1)
	{
		OLED_ShowNum(1,5,Num,5);
		OLED_ShowNum(2,5,Timer_GetCounter(),5);
		OLED_ShowNum(3,5,GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5),1);
	}               
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
	}
}
