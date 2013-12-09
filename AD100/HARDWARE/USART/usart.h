#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include <stm32f10x.h>

void Usart485_ControlInit(void);
void Usart485_Enable(void);
void Usart485_Disable(void);
void Usart_Init(USART_TypeDef *usart, int baudRate);
void Send_Data(USART_TypeDef* usartx, uint16_t data);
void Send_String(USART_TypeDef* usartx, uint16_t *str);

#endif
