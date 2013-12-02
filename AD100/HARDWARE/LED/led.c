#include "stm32f10x.h"
#include "led.h"
		    
//LED IO��ʼ��
void LED_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 	//ʹ��PA�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 	//ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 	//PA.12Ϊ״̬����˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 	//PA.12 �����

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 	//PA.12Ϊ״ָ̬ʾ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);						 	//PC.9 �����
}
 
