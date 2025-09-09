#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "Servo.h"
#include "Serial.h"

int16_t AX, AY, AZ, GX, GY, GZ;
double Temp, Angle = 0;

int main(void)
{
	OLED_Init();
	MPU6050_Init();//含串口初始化
	Servo_Init();
	
	Servo_SetAngle(Angle);
	
	OLED_ShowString(1,1,"ID:");
	uint8_t ID = MPU6050_GetID();
	OLED_ShowHexNum(1,4,ID,2);
	
	
	while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		if (Serial_GetRxFlag() == 1)
		{
			//C语言会根据数据正负进行符号扩展，串口传输无符号数，先转换为有符号数再赋值double
			Temp = (int8_t)Serial_GetRxData();
			Angle = Temp / 4; //传输时扩展到8位将30扩大为120
			if (Angle > 90) Angle = 0;
			if (Angle < -90) Angle = 0;
			Servo_SetAngle(Angle);
		}
		OLED_ShowSignedNum(1,13,Angle,3);
		OLED_ShowString(1,7,"Angle:");
		OLED_ShowSignedNum(2,1,AX,5);
		OLED_ShowSignedNum(3,1,AY,5);
		OLED_ShowSignedNum(4,1,AZ,5);
		OLED_ShowSignedNum(2,8,GX,5);
		OLED_ShowSignedNum(3,8,GY,5);
		OLED_ShowSignedNum(4,8,GZ,5);		
	}               
}
