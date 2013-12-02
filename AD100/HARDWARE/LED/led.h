#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

//LED端口定义
#define StateLED PCout(9)// PC9,状态指示灯

void LED_Init(void);//初始化

		 				    
#endif
