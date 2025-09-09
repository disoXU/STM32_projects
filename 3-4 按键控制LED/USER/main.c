#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t KeyNum;

int main(void)
{
	LED_Init();
	Key_Init();
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 2) LED1_Turn();
		if (KeyNum == 3) LED2_Turn();
	}               
}
