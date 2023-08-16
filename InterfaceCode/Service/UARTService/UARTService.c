#include "STDTYPES.h"
#include "UARTService.h"
#include "UART.h"


void  UART_VoidWriteString(char *str)
{
	for(u8 i=0;str[i];i++)
	{
		UART_VoidWriteDataChar(str[i]);
		
	}
}

void UART_VoidReadString(u8 *str)
{
	u8 i=0;
	str[i]=UART_U8ReadData();
	for(;str[i]!='#';)
	{
		i++;
		str[i]=UART_U8ReadData();
	}
	str[i]=0;
	
}

void UART_WriteNumber(u32 num)
{
	u8*P=&num;
	for(u8 i=0;i<4;i++)
	{
		UART_VoidWriteDataChar(P[i]);
	}
}

u32 UART_ReadNumber(void)
{
	u32 num;
	u8 b0=UART_U8ReadData();
	u8 b1=UART_U8ReadData();
	u8 b2=UART_U8ReadData();
	u8 b3=UART_U8ReadData();
	num=(u32)b0 | (u32)b1<<8  | (u32)b2<<16  | (u32)b3<<24 ;
	return num;
}

u32 UART_ReadNumber1(void)
{
	u32 num;
	u8 *ptr=&num;
	for(u8 i=0;i<4;i++)
	{
		ptr[i]=UART_U8ReadData();
	}
	return num;
}

/**************************little endian********************/
u8 checksystem(void)
{
	u32 x=1;
	u8 *ptr=&x;
	if(*ptr==1)
	{
		return 1;// little endian
	}
	else
	{
		return 0;
	}
}

u16 Convert(u16 x)
{
	u16 y=x>>8 | x<<8;
	return y;
	/*u8 *ptr=&x;
	u8 temp=ptr[0];
	ptr[0]=ptr[1];
	ptr[1]=temp;*/
}

u32 convert2(u32 x)
{
	u32 b1=x>>24;
	u32 b4=x<<24;
	u32 b2=x>>8 & 0x0000FF00;
	u32 b3=x<<8 & 0x00FF0000;
	u32 y=b1|b2|b3|b4;
	return y;
	
	
	/*u8 *ptr=&x;
	u8 temp=ptr[0];
	ptr[0]=ptr[3];
	ptr[3]=temp;
	u8 temp2=ptr[1];
	ptr[1]=ptr[2];
	ptr[2]=temp;*/
	
}

u8 CompareString(u8 *str1,u8 *str2)
{
	for(u8 i=0;str1[i]||str2[i] ;i++)
	{
		if(str1[i] !=str2[i])
		{
			return 0;// not matching
		}
	}
	
	return  1;
}

void UART_SENDStringWithCheckSum(u8*str)
{
	u8 len=0;
	u16 sum=0;
	for(len=0;str[len];len++)
	{
		
	}
	UART_VoidWriteDataChar(len);
	for(u8 i=0;str[i];i++)
	{
		UART_VoidWriteDataChar(str[i]);
		sum+=str[i];
	}
	UART_VoidWriteDataChar((u8)sum);
	UART_VoidWriteDataChar((u8)(sum>>8));
}

UARTFRAME_ErrorType UART_RecieveStringWithCheckSum(u8 *str)
{
	u8 len=UART_U8ReadData();
	u16 sumRec=0,sumCal=0;
	for(u8 i=0;i<len;i++)
	{
		str[i]=UART_U8ReadData();
		sumCal+=str[i];
		
	}
	u8 sum0=UART_U8ReadData();
	u8 sum1=UART_U8ReadData();
	sumRec= (u16) sum0 |(u16) (sum1 <<8);
	
	if(sumCal==sumRec)
	{
		return FrameOk;
	}
	else
	{
		return FrameError;
	}
}


/*if(UART_RecieveStringWithCheckSum(str)==FrameOk)
{
	LCD_WriteString(str);
}
else
{
	LCD_WriteString("Frame Error");
}*/

// Receive data from UART using Interrupt
