#include "extit.h"
#include "delay.h"


//外部中断初始化程序
//初始化PA11为中断输入.
void EXTIX_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;


  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);

  	//init GPIOA.11 上拉输入
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_11);

  	//GPIOA.11
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//先占优先级4位,共16级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//先占优先级0位,从优先级4位
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
}


void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);
    if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
		ready_flag = 1;
	}
	EXTI_ClearITPendingBit(EXTI_Line11);  //清除标志
}
