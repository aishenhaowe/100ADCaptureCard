#include "crc.h"

u8 Crc8(u8 *PData, u8 Len)
{
	u8 Crc;
	u8 ch[8], ch1;
	u8 i, j, k;
	
	Crc = 0xff;
	for (i=0;i<Len;i++)
	{
		ch1 = PData[i];
		for (j=0;j<8;j++)
		{
			ch[j] = ch1 & 0x01;
			ch1 >>= 1;
		}
		for (k=0;k<8;k++)
		{
			ch[7-k] <<=7;
			if ((Crc ^ ch[7-k]) & 0x80)
			Crc = (Crc << 1)^0x1d ;
			else
			Crc <<= 1;
		}
	}
	Crc ^= 0xff;
	return  Crc;
}
