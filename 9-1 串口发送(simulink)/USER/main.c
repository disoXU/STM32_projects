#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main(void)
{
	OLED_Init();
	Serial_Init();
	
//	Serial_SendByte(0x41);
//	
//	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
//	Serial_SendArray(MyArray, 4);
//	
//	Serial_SendString("\r\nHelloWorld!\r\n");
//	Serial_SendNum(12345,5);
//	
//	printf("\r\nNum1=%d\r\n", 666);//重写printf函数，在Serial.c文件中
//	
//	char String[100];
//	sprintf(String, "Num2=%d\r\n", 888); //将格式化数据写入字符串
//	Serial_SendString(String);
//	
//	printf("\n");
	
	while(1)
	{
//		uint8_t MyArray[] = {0x41, 0x20, 0x42, 0x20, 0x43, 0x20, 0x0A};
//		Serial_SendArray(MyArray, 7);
		uint8_t MyArray[] = {0x41, 0x42, 0x43, 0x0A};
		Serial_SendArray(MyArray, 4);
		Delay_ms(100);
	}               
}
