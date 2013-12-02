#include "stm32f10x.h"
#include "led.h"
		    
//LED IO初始化
void LED_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 	//使能PA端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 	//使能PC端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 	//PA.12为状态输出端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 	//PA.12 输出低

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 	//PA.12为状态指示灯
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);						 	//PC.9 输出低
}
 
