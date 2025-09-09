#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"

uint8_t KeyNum;
float Angle = 0;

int main(void)
{
	OLED_Init();
	Servo_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"Angle:");

	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 2)
		{
			Angle += 30;
			if (Angle > 90)
			{
				Angle = 0;
			}
		}
		if (KeyNum == 3)
		{
			Angle -= 30;
			if (Angle < -90)
			{
				Angle = 0;
			}
		}
		Servo_SetAngle(Angle);
		OLED_ShowSignedNum(1,7,Angle,3);
	}               
}
