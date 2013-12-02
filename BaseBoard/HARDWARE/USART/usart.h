#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include <stm32f10x.h>
#include <delay.h>

void Usart_Init(USART_TypeDef *usart, int baudRate);
void Send_Data(USART_TypeDef* usartx, uint16_t data);
void Send_String(USART_TypeDef* usartx, char *str);

#endif
