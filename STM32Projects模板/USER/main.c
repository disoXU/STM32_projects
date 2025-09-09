#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR = 0x00000040;
	GPIOG->MODER = 0x00010050;
	GPIOG->OTYPER = 0x00000000;
	GPIOG->OSPEEDR = 0x000200A0;
	GPIOG->PUPDR = 0x00000000;
	GPIOG->ODR = 0x0000FFF3;
	while(1)
	{
		
	}
}
