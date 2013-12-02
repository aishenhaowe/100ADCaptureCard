#include "led.h"
#include "boardonline.h"
#include "delay.h"
#include "sys.h"
#include "doublelink.h"
#include "usart.h"

int main(void)
{
	int i = 0;

	struct link onlineBoardList;
	data_t data;

	link_init(&onlineBoardList);

	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();			     //LED端口初始化
	Usart_Init(USART1, 9600);
	OnlineKey_Init();

	for(i = 0; i < 10; i++)
	{
		char num = GPIO_ReadInputDataBit(GPIOB, 1 << (i + 6));
		if(num == 1)
		{
			data.data = i;
			link_add(&onlineBoardList, &data);

			GPIO_SetBits(GPIOC, GPIO_Pin_15);
			Send_String(USART1, "On\n");
			delay_ms(500);
			GPIO_ResetBits(GPIOC, GPIO_Pin_15);
			Send_String(USART1, "Off\n");
			delay_ms(500);
		}
	}

	while(1)
	{
		struct node *cur ;
		for(cur = onlineBoardList.head.next; cur != &onlineBoardList.head; cur = cur->next)
		{
			char isBusy = GPIO_ReadInputDataBit(GPIOB, 1 << (cur->data.data + 6));	
			if(isBusy == 1)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_14);

				GPIO_SetBits(GPIOA, 1 << cur->next->data.data);
				Send_String(USART1, "On\n");
				delay_ms(10);
				GPIO_ResetBits(GPIOA, 1 << cur->next->data.data);
				Send_String(USART1, "Off\n");

				while(isBusy)
				{
					isBusy = (GPIO_ReadInputDataBit(GPIOB, 1 << (cur->data.data + 6)) == 0);
				}

				GPIO_ResetBits(GPIOC, GPIO_Pin_14);
			}
		}
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
  }
}

#endif
