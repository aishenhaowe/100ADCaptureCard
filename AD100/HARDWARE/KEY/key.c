#include "key.h"

void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( KEY1_RCC 
						| KEY2_RCC 
						| KEY3_RCC 
						| KEY4_RCC , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  KEY1_GPIO;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(KEY1_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  KEY2_GPIO; 
	GPIO_Init(KEY2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  KEY3_GPIO; 
	GPIO_Init(KEY3_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  KEY4_GPIO; 
	GPIO_Init(KEY4_PORT, &GPIO_InitStructure);
}

u8 Read_Key(void)
{
	char byte1, byte2, byte3, byte4, result;
	byte1 = GPIO_ReadInputDataBit(KEY1_PORT,KEY1_GPIO);
	byte2 = GPIO_ReadInputDataBit(KEY2_PORT,KEY2_GPIO);
	byte3 = GPIO_ReadInputDataBit(KEY3_PORT,KEY3_GPIO);
	byte4 = GPIO_ReadInputDataBit(KEY4_PORT,KEY4_GPIO);

	result =  byte1 | (byte2 << 1) | (byte3 << 2) | (byte4 << 3);
	return result;
} 
