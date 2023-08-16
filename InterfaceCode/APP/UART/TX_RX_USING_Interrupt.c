#include  "MemoryMap.h"
#include  "UART.h"
#include  "UARTSTACK.h"
#include  "LCD_Interface.h"
#include  "TX_RX_USING_Interrupt.h"
#include  "Interrupt.h"


/**************************RECIEVE DATA USING INterr upt*********************************/
static volatile u8 arr[20];
static volatile FlagRecieve=0;
static u8 i=0,x=0;

void FUN_RX(void)
{
	u8 static i=0;
	arr[i]=UART_ReceiveByteNoBlock();
	i++;
	FlagRecieve++;
}

void UART_USING_Interrupt_Init(void)
{
	 sei();
	 UART_RXCIE_SetCallBack(&FUN_RX);
	 UART_RXComplete_InterruptEnable(); 
}


void UART_RECIEVE_DATA_USING_Interrupt_Runnable(void)
{
	
	 LCDGoTo(0,0);
	 LCD_WriteNumber(x);
	 x++;
	 if(x==10)
	 {
		 x=0;
	 }
	 _delay_ms(10000);
	 
	 
	 if(FlagRecieve>1)
	 {
		 LCDGoTo(1,i);
		 LCD_WriteChar(arr[i]);
		 i++;
		 FlagRecieve--;
	 }
}


//===================================================================================================================
//=======================RECEIVE DATA ASY FROM UART USING Interrupt but save it in specific array===================

static volatile u8* RXSTR;

void UART_RX_ASY_INSECIFICBUFFER(void)
{
	static u8 i=0;
	RXSTR[i]=UART_ReceiveByteNoBlock();
	i++;
}

void UART_RECIVE_ASY_USINGINTERRUPT_INSPECIFICBUFFRE_INIT(u8 * str)
{
	
	 sei();
	 UART_RXCIE_SetCallBack(&FUN_RX);
	 UART_RXComplete_InterruptEnable();
	 RXSTR=str;
}

///===========================RECICEVE DOUBLE BUFFER 8 BYTE IN EACH BUFFER USING INTERRUPT ASY============

static u8 BUFFER1[8];
static u8 BUFFER2[8];
static volatile u8 BUFFERflag=0;
static volatile u8 DATAREADYLAG=0;

void UART_RX_INTWO_BUFFER(void)
{
	static u8 i=0;
	
	if(BUFFERflag==0)
	{
		BUFFER1[i]=UART_ReceiveByteNoBlock();
	}
	else
	{
		BUFFER2[i]=UART_ReceiveByteNoBlock();
	}
	i++;
	if(i==8)
	{
		i=0;
		BUFFERflag=BUFFERflag^1;
		DATAREADYLAG=1;
	}
	
}


void UART_Rx_INTWOBUFFER_8BYTEDATA_USING_INTERRUPT_ASY_INIT(void)
{
	 sei();
	 UART_RXCIE_SetCallBack(&FUN_RX);
	 UART_RXComplete_InterruptEnable();
}


u8  UART_Rx_INTWOBUFFER_8BYTEDATA_USING_INTERRUPT_ASY(u8 *str)
{  
	
	if(DATAREADYLAG==0)
	{
		return 0;
	}
	for(u8 i=0;i<8;i++)
	{
		if(BUFFERflag==0)
		{
			str[i]=BUFFER2[i];
		}
		else
		{
			str[i]=BUFFER1[i];
		}
	}
	DATAREADYLAG=0;
	return 1;
}

void UART_Rx_INTWOBUFFER_8BYTEDATA_USING_INTERRUPT_ASY_RUNNABLE(u8 *str)
{
	if(UART_Rx_INTWOBUFFER_8BYTEDATA_USING_INTERRUPT_ASY(str)==1)
	{
		LCDGoTo(0,0);
		LCD_WriteString(str);
	}
}

//======================================================================================



/**************************Send DATA USING Interrupt*********************************/
u8 *TXR;
static volatile BusyFlag=1;

void FUN_TX(void)
{
	static u8 i=1;
	if(TXR[i] !=0)
	{
		UART_SendByteNoBlock(TXR[i]);
		i++;
	}
	else
	{
		BusyFlag=0;
		i=1;
	}
}
void UART_SENDSTRING_Asyn_UsingInterrupt_Init(void)
{
	 sei();
	 UART_TXCIE_SetCallBack(&FUN_TX);
	 UART_TXComplete_InterruptEnable();
}


void UART_SENDSTRING_Asyn_UsingInterrupt_Runnable(u8 *str)
{
	UART_SendByteNoBlock(str[0]);
	TXR=str;
	
	/*to sending asyn not disable code	inside while one==
	
	 LCDGoTo(0,0);
	 LCD_WriteNumber(x);
	 x++;
	 if(x==10)
	 {
		 x=0;
	 }
	 _delay_ms(10000);*/
	
	
}

/********************************send data async using interrupt to set flag then send data with regular rate in main function********************************/
static volatile SendFlag=1;

void FUN_TX2(void)
{
	SendFlag=1;
}

void UART_SendData_Asynch_UsingInterrupt_TosetFlag_ThenSendData_inMainFun_Init(void)
{
	sei();
	UART_TXCIE_SetCallBack(&FUN_TX2);
	UART_TXComplete_InterruptEnable();
}

void UART_SendData_Asynch_UsingInterrupt_TosetFlag_ThenSendData_inMainFun_Runnable(u8 *str)
{
	
	
	static u8 i=0;	
	if(SendFlag==1)
	{
		if(str[i] !=0)
		{
			
			UART_SendByteNoBlock(str[i]);
			i++;
			
		}
		else
		{
			i=0;
			SendFlag==1;
		}
		
	    SendFlag==0;	
	}
	
}
/*************************************************************************************************************************/
//PUSH DATA IN UART USING STACK 
static volatile STACKFULLFLAG=0,POPFLAG=0;
static u8 Data;

void UARTSTACK_RX(void)
{	
	u8 data=UART_ReceiveByteNoBlock();
	if(UART_PUSHBYTE(data)==SATCKfULL)
	{
		STACKFULLFLAG=1;
	}
}

// POP DATA FROM UART USING STACK WHEN BUSH BUTTON IS PRESSED
void UARTPOP(void)
{
	POPFLAG=1;
}


void UART_RECIEVEDATAUSINGSTACKSTRUCTURE_INIT(void)
{
	sei();
	UART_RXCIE_SetCallBack(&UARTSTACK_RX);
	UART_RXComplete_InterruptEnable();
}

void UART_USINGSTACKSTRUCTRUEUSINGBUTTONTOPOPDATA(void)
{
	Ext_SetCallBack(Interrupt_INT0,UARTPOP);
	ExternalInterruptEnable(Interrupt_INT0);
	ExternalInttruptwillbeActivatedWith(Interrupt_INT0,NegativeEdge);	
}

void UART_PUSH_POPDATAUSING_STACK_Runnable(void)
{
	
	if(STACKFULLFLAG==1)
	{		
		UART_VoidWriteString("STACK FULL");
		LCDGoTo(1,0);
		LCD_WriteString("STACKFULL");
		STACKFULLFLAG=0;
	}
	if(POPFLAG==1)
	{
		if(UART_POPBYTE(&Data)==STACKEMPTY)
		{
			LCDGoTo(1,0);
			LCD_WriteString("STACKEMPTY");
		}
		else
		{
			LCDGoTo(0,10);
			LCD_WriteChar(Data);
		}
		
		POPFLAG=0;
	}
	
}