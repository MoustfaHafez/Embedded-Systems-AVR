 #include "MacrosLikeFunction.h"
 #include "STDTYPES.h"
 #include "DIO_Interafce.h"
 #include "LCD_Interface.h"
 #include "UART.h"     
 #include "UARTService.h"
 #include "DockLight.h"
 
 static u8 MessagFromUART[20];
 static u8 StrMessage[10];
 static u8 NumMessage=0;
 static u8 flag1=0;
 

UARTTASK_Type arr[size]={{"LEDON",&LEDONN},{"LEDOFF",&LEDOFFF}};
	 
	 
void LEDONN(u8 num)
{
	switch(num)
	{
		case 0:
		DIO_VidWritePin(PINC0,High);
		break;
		case 1:
		DIO_VidWritePin(PINC1,High);
		break;
		case 2:
		DIO_VidWritePin(PINC2,High);
		break;
		
	}
}

void LEDOFFF(u8 num)
{
	switch (num)
	{
		case 0:
		DIO_VidWritePin(PINC0,Low);
		break;
		case 1:
		DIO_VidWritePin(PINC1,Low);
		break;
		case 2:
		DIO_VidWritePin(PINC2,Low);
		break;	
	}
}

void ReadMessagefromUART(void)
{
	
	 UART_VoidReadString(MessagFromUART);
	
}
 void DisplayMessagefromUART(void)
 {
	  LCDGoTo(0,0);
	  LCD_WriteString(MessagFromUART);
	  LCD_WriteString("          ");
 }

void SplitStringFromUARTintoStringAndNum(void)
{
	
	for(u8 i=0;MessagFromUART[i];i++)
	{
		if(MessagFromUART[i]!=' '&& flag1!=1)
		{
			StrMessage[i]=MessagFromUART[i];
		}
		else
		{
			if(MessagFromUART[i]==' ')
			{
				flag1=1;
				StrMessage[i]=0;
				continue;
			}
			
			NumMessage=NumMessage*10+(MessagFromUART[i]-'0');
		}
	}	
}

void DisplayStringMessageAndNumAfterSplitting(void)
{
	LCDGoTo(1,0);
	LCD_WriteString(StrMessage);
	LCD_WriteString("  ");
	LCD_WriteNumber(NumMessage);
	LCD_WriteString("                      ");
}

 void CompareStringofUARTwithStringOfArr(void)
 {
	 	
	 	for(u8 i=0;i<size;i++)
	 	{
		 	if(CompareString(StrMessage,arr[i].str))
		 	{
			 	arr[i].pf(NumMessage);
		 	}
		 	else
		 	{
			 	LCD_WriteString("ERROR MESSAGE");
		 	}
	 	}
	 	
 }
 
  void RestFlagAndNum(void)
  {
	   flag1=0;
	   NumMessage=0;
  }
 
 void UARTTASK_Runnable(void)
 {
	 ReadMessagefromUART();
	 DisplayMessagefromUART();
	 SplitStringFromUARTintoStringAndNum();
	 DisplayStringMessageAndNumAfterSplitting();
	 CompareStringofUARTwithStringOfArr();
	 RestFlagAndNum();
 }

