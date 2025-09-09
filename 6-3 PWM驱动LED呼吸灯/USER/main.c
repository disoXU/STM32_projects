#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint8_t i;

int main(void)
{
	OLED_Init();
	PWM_Init();
	
	OLED_ShowString(1,1,"PA5:");

	while(1)
	{
		OLED_ShowNum(1,5,GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5),1);
		for (i=0; i<=100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for (i=0; i<=100; i++)
		{
			PWM_SetCompare1(100 - i);
			Delay_ms(10);
		}
	}               
}
