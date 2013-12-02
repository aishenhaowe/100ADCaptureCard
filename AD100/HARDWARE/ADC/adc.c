#include "adc.h"	   
//��ʼ��ADC
//�Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~15,ADC����ģʽΪɨ��ģʽ																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure;//����ADC��ʼ���ṹ�� 
	GPIO_InitTypeDef GPIO_InitStructure; //����GPIO��ʼ���ṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1,ENABLE);	 
																	 //ʹ��GPIO��ADC1ͨ��ʱ��

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA0/1/2/3/4/5/6/7����8��GPIO��Ϊģ��ͨ���������ţ��趨GPIO״̬����ʼ��                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
								  GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//PB0/1����2��GPIO��Ϊģ��ͨ���������ţ��趨GPIO״̬����ʼ�� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	//PC0/1/2/3/4/5����6��GPIO��Ϊģ��ͨ���������ţ��趨GPIO״̬����ʼ�� 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
//								  GPIO_Pin_4|GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
//	GPIO_Init(GPIOC, &GPIO_InitStructure);	


	ADC_DeInit(ADC1);  //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڶ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 10;	//˳����й���ת����ADCͨ������Ŀ

	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ��� 
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��0,�������˳��ֵΪ1,����ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��1,�������˳��ֵΪ2,����ʱ��Ϊ239.5���� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��2,�������˳��ֵΪ3,����ʱ��Ϊ239.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��3,�������˳��ֵΪ4,����ʱ��Ϊ239.5���� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��4,�������˳��ֵΪ5,����ʱ��Ϊ239.5���� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��5,�������˳��ֵΪ6,����ʱ��Ϊ239.5���� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��6,�������˳��ֵΪ7,����ʱ��Ϊ239.5���� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��7,�������˳��ֵΪ8,����ʱ��Ϊ239.5���� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 9, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��8,�������˳��ֵΪ9,����ʱ��Ϊ239.5���� 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 10, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��9,�������˳��ֵΪ10,����ʱ��Ϊ239.5���� 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 11, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��10,�������˳��ֵΪ11,����ʱ��Ϊ239.5���� 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 12, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��11,�������˳��ֵΪ12,����ʱ��Ϊ239.5���� 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 13, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��12,�������˳��ֵΪ13,����ʱ��Ϊ239.5���� 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 14, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��13,�������˳��ֵΪ14,����ʱ��Ϊ239.5���� 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 15, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��14,�������˳��ֵΪ15,����ʱ��Ϊ239.5���� 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 16, ADC_SampleTime_55Cycles5 );	//ADC1,ADCͨ��15,�������˳��ֵΪ16,����ʱ��Ϊ239.5���� 
	   

	
    ADC_DMACmd(ADC1, ENABLE); //ʹ��ADC1��DMA����												  7.5 cycles
 

	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1	  
	ADC_ResetCalibration(ADC1);	//����ָ����ADC1��У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));	//��ȡADC1����У׼�Ĵ�����״̬,����״̬��ȴ�
	ADC_StartCalibration(ADC1);		//��ʼָ��ADC1��У׼״̬
	while(ADC_GetCalibrationStatus(ADC1));		//��ȡָ��ADC1��У׼����,����״̬��ȴ�
}	

			  




























