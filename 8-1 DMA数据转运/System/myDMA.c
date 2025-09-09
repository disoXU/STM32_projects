#include "stm32f4xx.h"                  // Device header

uint16_t MyDMA_Size;

void myDMA_Init(uint32_t AddrP, uint32_t AddrM, uint16_t Size)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE);
	
	DMA_InitTypeDef DMA_InitStructure; //通道配置
	DMA_InitStructure.DMA_Channel = DMA_Channel_0; //选择通道
	DMA_InitStructure.DMA_BufferSize = Size; //缓冲区大小即传输计数器
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //是否自动重装，存储器到存储器时循环模式禁用
	
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable; //启用FIFO结构，禁用直接模式
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull; //设置阈值，传输数据达到字节立刻进行转运
	
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory; //传输方向，M2M默认外设区转运到存储区
	
	DMA_InitStructure.DMA_Memory0BaseAddr = AddrM; //存储区地址
	DMA_InitStructure.DMA_MemoryBurst= DMA_MemoryBurst_Single; //突发传输数量
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //字节宽度
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrP; //外设区地址
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //优先级设置
	
	DMA_Init(DMA2_Stream0 ,&DMA_InitStructure); //为数据流配置通道参数，数据流0选择了通道0
	
	DMA_Cmd(DMA2_Stream0, DISABLE);//使能DMA2数据流0
	
	MyDMA_Size = Size;
	//while(DMA_GetCmdStatus(DMA2_Stream0) != ENABLE);
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA2_Stream0, DISABLE);
	while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE);
	
	DMA_SetCurrDataCounter(DMA2_Stream0, MyDMA_Size);
	DMA_Cmd(DMA2_Stream0, ENABLE);
	while(DMA_GetCmdStatus(DMA2_Stream0) != ENABLE);
	
	while(DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0) == RESET);
	DMA_ClearFlag(DMA2_Stream0, DMA_FLAG_TCIF0);
}
