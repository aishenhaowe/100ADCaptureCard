#include "adc.h"	   
//初始化ADC
//以规则通道为主
//我们默认将开启通道0~15,ADC工作模式为扫描模式																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure;//定义ADC初始化结构体 
	GPIO_InitTypeDef GPIO_InitStructure; //定义GPIO初始化结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1,ENABLE);	 
																	 //使能GPIO与ADC1通道时钟

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC最大时间不能超过14M

	//PA0/1/2/3/4/5/6/7共计8个GPIO作为模拟通道输入引脚，设定GPIO状态并初始化                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
								  GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//PB0/1共计2个GPIO作为模拟通道输入引脚，设定GPIO状态并初始化 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	//PC0/1/2/3/4/5共计6个GPIO作为模拟通道输入引脚，设定GPIO状态并初始化 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
//								  GPIO_Pin_4|GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
//	GPIO_Init(GPIOC, &GPIO_InitStructure);	


	ADC_DeInit(ADC1);  //将外设 ADC1 的全部寄存器重设为缺省值
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在多通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 10;	//顺序进行规则转换的ADC通道的数目

	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器 
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道0,规则采样顺序值为1,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道1,规则采样顺序值为2,采样时间为239.5周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道2,规则采样顺序值为3,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道3,规则采样顺序值为4,采样时间为239.5周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道4,规则采样顺序值为5,采样时间为239.5周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道5,规则采样顺序值为6,采样时间为239.5周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道6,规则采样顺序值为7,采样时间为239.5周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道7,规则采样顺序值为8,采样时间为239.5周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道8,规则采样顺序值为9,采样时间为239.5周期 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道9,规则采样顺序值为10,采样时间为239.5周期 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道10,规则采样顺序值为11,采样时间为239.5周期 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道11,规则采样顺序值为12,采样时间为239.5周期 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道12,规则采样顺序值为13,采样时间为239.5周期 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 14, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道13,规则采样顺序值为14,采样时间为239.5周期 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 15, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道14,规则采样顺序值为15,采样时间为239.5周期 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 16, ADC_SampleTime_55Cycles5 );	//ADC1,ADC通道15,规则采样顺序值为16,采样时间为239.5周期 
	   

	
    ADC_DMACmd(ADC1, ENABLE); //使能ADC1的DMA传输												  7.5 cycles
 

	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1	  
	ADC_ResetCalibration(ADC1);	//重置指定的ADC1的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1重置校准寄存器的状态,设置状态则等待
	ADC_StartCalibration(ADC1);		//开始指定ADC1的校准状态
	while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待
}	

			  




























