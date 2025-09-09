#include "stm32f4xx.h"                  // Device header
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)BitValue);
	Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)BitValue);
	Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
	Delay_us(10);
	return BitValue;
}

void MyI2C_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,	GPIO_Pin_8 | GPIO_Pin_9);
}

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);	
	MyI2C_W_SCL(1);//����˳���ܱ䣬Ϊ�˼����ظ���ʼ����
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);//˳����Ȼ���ܱ�
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80 >> i));
		MyI2C_W_SCL(1);//SCLΪ1ʱ���ӻ����ȡSDA�ϵ�����
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;
	MyI2C_W_SDA(1);//�����ͷ�SDA���ӻ����ܲ���SDA�ߣ�SDA�ͷź󱻴ӻ����ͱ����ӻ����յ�����
	for(i=0;i<8;i++)
	{
		MyI2C_W_SCL(1);//����ߵ�ƽ������׼����ȡSDA
		if (MyI2C_R_SDA() == 1) {Byte |= (0x80 >> i);}
		MyI2C_W_SCL(0);//ͨ���У�SCL��0�ӻ���ı�SDA��ֵ������������ȡSDA��������
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);//�����ͷ�SDA���ӻ����ܲ���SDA�ߣ�SDA�ͷź󱻴ӻ����ͱ����ӻ����յ�����
	MyI2C_W_SCL(1);//����ߵ�ƽ������׼����ȡSDA
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}

