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

u16 ADC_Value[NumOfAdConvert][NumOfAdcChanel];	//���ADCת����Ľ����Ҳ��DMA�ĵ�ַ
u16 After_filter[NumOfAdcChanel];				//���ƽ��֮���ADC���
u8	TransferBuff[TransferBuffLen];			    //���ͻ�����

//���㷢�ͻ�����������
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

//�Բɼ������ݽ�����ƽ��ֵ
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
	SystemInit(); 			 //ϵͳʱ�ӳ�ʼ��Ϊ72M	  SYSCLK_FREQ_72MHz
	delay_init(72);	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();			     //LED�˿ڳ�ʼ��
	StateLED = 1;			 //����״ָ̬ʾ��
	Usart_Init(USART1, 9600);
	EXTIX_Init();
	Adc_Init();
	Key_Init();
	//����DMA:DMA1ͨ��1,����ΪADC1,�洢��ΪADC_Value,����NumOfAdConvert*NumOfAdcChanel.
	DMA_Config(DMA1_Channel1, (u32)&ADC1->DR, (u32)&ADC_Value, NumOfAdConvert*NumOfAdcChanel);
	DMA_Cmd(DMA1_Channel1, ENABLE);//����DMA
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//�������ָ����ADC����
	
	delay_ms(2000);
	StateLED = 0;			//Ϩ��״ָ̬ʾ��
	while(1)
	{
		if(ready_flag == 1)
		{
			if(DMA_GetFlagStatus(DMA1_FLAG_TC1))
			{
				StateLED = 1;						//��״ָ̬ʾ��
				GPIO_ResetBits(GPIOA, GPIO_Pin_12);	//״̬����˿����0,��ʾæµ
				filter();
				CalculateTransferBuff(After_filter);
				TransferData(USART1, TransferBuff, TransferBuffLen);
				ready_flag = 0;
//				delay_ms(1000);
				StateLED = 0;						//�ر�״ָ̬ʾ��
				GPIO_SetBits(GPIOA, GPIO_Pin_12);	//״̬����˿����1,��ʾ����

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
