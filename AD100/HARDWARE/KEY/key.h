#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

#define KEY1_GPIO	GPIO_Pin_15
#define KEY2_GPIO	GPIO_Pin_14
#define KEY3_GPIO	GPIO_Pin_13
#define KEY4_GPIO	GPIO_Pin_12

#define KEY1_PORT	GPIOB
#define KEY2_PORT	GPIOB
#define KEY3_PORT	GPIOB
#define KEY4_PORT	GPIOB

#define KEY1_RCC	RCC_APB2Periph_GPIOB
#define KEY2_RCC	RCC_APB2Periph_GPIOB
#define KEY3_RCC	RCC_APB2Periph_GPIOB
#define KEY4_RCC	RCC_APB2Periph_GPIOB

void Key_Init(void);
u8 Read_Key(void);

#endif
