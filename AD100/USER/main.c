#include "led.h"
#include "usart.h"
#include "adc.h"
#include "delay.h"
#include "sys.h"
#include "dma.h"
#include "extit.h"
#include "key.h"
#include "crc.h"

#define NumOfAdcChanel	10
#define NumOfAdConvert	20
#define TransferBuffLen	24
char ready_flag = 0;

u16 ADC_Value[NumOfAdConvert][NumOfAdcChanel];	//存放ADC转换后的结果，也是DMA的地址
u16 After_filter[NumOfAdcChanel];				//存放平均之后的ADC结果
u8	TransferBuff[TransferBuffLen];			    //发送缓存区

//计算发送缓存区的内容
void CalculateTransferBuff(u16 *buff)
{
	int i = 0;
	for(i = 0; i < NumOfAdcChanel; i++)
	{
		TransferBuff[2 * i + 3] = buff[i] & 0xFF;
		TransferBuff[2 * i + 2] = (buff[i] >> 8) & 0xFF; 
	}
	TransferBuff[0] = Read_Key();
	TransferBuff[1] = 10;
	TransferBuff[TransferBuffLen - 2] = Crc8(TransferBuff, TransferBuffLen - 2);
	TransferBuff[TransferBuffLen - 1] = 0x0A;
}

void TransferData(USART_TypeDef *usartx, u8 *buff, int buffLen)
{
	int i = 0;
	for(i = 0; i < buffLen; i++)
	{
		StateLED = 1;
		Send_Data(usartx, buff[i]);		
		delay_ms(1);
		StateLED = 0;
	}	
}

//对采集的数据进行求平均值
void filter(void)
{
	int sum = 0;
	u8 count;
	int i = 0;   
	for(i=0; i<NumOfAdcChanel; i++)
	{
		for(count=0;count<NumOfAdConvert;count++)
		{
			sum += ADC_Value[count][i];
		}
		After_filter[i]=sum/NumOfAdConvert;
		sum=0;
	}
}

int main(void)
{
	SystemInit(); 			 //系统时钟初始化为72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();			     //LED端口初始化
	StateLED = 1;			 //点亮状态指示灯
	Usart_Init(USART1, 9600);
	EXTIX_Init();
	Adc_Init();
	Key_Init();
	//配置DMA:DMA1通道1,外设为ADC1,存储器为ADC_Value,长度NumOfAdConvert*NumOfAdcChanel.
	DMA_Config(DMA1_Channel1, (u32)&ADC1->DR, (u32)&ADC_Value, NumOfAdConvert*NumOfAdcChanel);
	DMA_Cmd(DMA1_Channel1, ENABLE);//启动DMA
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件启动指定的ADC功能
	
	delay_ms(2000);
	StateLED = 0;			//熄灭状态指示灯
	while(1)
	{
		if(ready_flag == 1)
		{
			if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
			{
				StateLED = 1;						//打开状态指示灯
				GPIO_ResetBits(GPIOA, GPIO_Pin_12);	//状态输出端口输出0,表示忙碌
				filter();
				CalculateTransferBuff(After_filter);
				TransferData(USART1, TransferBuff, TransferBuffLen);
				ready_flag = 0;
//				delay_ms(1000);
				StateLED = 0;						//关闭状态指示灯
				GPIO_SetBits(GPIOA, GPIO_Pin_12);	//状态输出端口输出1,表示空闲

				ready_flag = 0;
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
