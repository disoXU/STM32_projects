#include "stm32f4xx.h"                  // Device header

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //开启外设时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; //设置模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_56Cycles); //配置规则组1为通道5，采样时间56个周期
	
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent; //单ADC模式
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;//配置ADCCLK
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//对于多ADC模式起作用
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Ext_IT11; //选择外部触发源
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //禁用外部触发源
	ADC_InitStructure.ADC_NbrOfConversion = 1; //设置规则组通道数
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; //设置ADC分辨率
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   //连续模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;   //扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);  //使能ADC
	
	ADC_SoftwareStartConv(ADC1); //软件触发ADC转换
}

uint16_t AD_GetValue(void)
{
	//ADC_SoftwareStartConv(ADC1);
	//while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}
