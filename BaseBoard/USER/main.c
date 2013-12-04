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

	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();			     //LED�˿ڳ�ʼ��
	GPIO_ResetBits(GPIOA, GPIO_Pin_13);
	OnlineKey_Init();

	for(i = 0; i < 10; i++)
	{
		char num = GPIO_ReadInputDataBit(GPIOB, 1 << (i + 6));
		if(num == 1)
		{
			data.data = i;
			link_add(&onlineBoardList, &data);
		}
	}

	while(1)
	{
		struct node *cur ;
		for(cur = onlineBoardList.head.next; cur != &onlineBoardList.head; cur = cur->next)
		{
			char isBusy = (GPIO_ReadInputDataBit(GPIOB, 1 << (cur->data.data + 6)) == 1);	
			if(isBusy == 0)
			{
				GPIO_SetBits(GPIOA, 1 << cur->data.data);
				delay_ms(10);
				GPIO_ResetBits(GPIOA, 1 << cur->data.data);

				while(isBusy)
				{
					isBusy = (GPIO_ReadInputDataBit(GPIOB, 1 << (cur->data.data + 6)) == 1);
				}
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
