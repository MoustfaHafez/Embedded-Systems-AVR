
#include "MemoryMap.h"
#include "DIO_Interafce.h"
#include "Sensors.h"
#include "SPIAPP.h"
#include "SPI.h"
#include "LCD_Interface.h"
#include "STDTYPES.h"
#include "Interrupt.h"


#define    F_CPU 8000000
#include  <util/delay.h>


static u16 TEMP;

//===================SLAVE============================


void READTEMPINSLAVE(void)
{
	TEMP=Temp_Read();
}

void DISPLAYTEMPOFSLAVE(void)
{
	LCDGoTo(1,0);
	LCD_WriteNumber(TEMP/10);
}

void SENDTemp(void)
{
	SPI_VoidSendNoBlock(TEMP/10);
}

void SPI_InterruptINIT(void)
{
	sei();
	SPI_InterruptEnable();
	SPI_SETCALLBACK(&SENDTemp);
}

void SLAVE_Init(void)
{
	SPI_InterruptINIT();
	SPI_VoidInitSlave();
}

void SLAVE_App_Runnable(void)
{
	READTEMPINSLAVE();
	DISPLAYTEMPOFSLAVE();
}

//====================================================
void SalveTriggerMasterToReceiveTemp(void)
{
	if(TEMP>400)
	{
		DIO_VidWritePin(PINB2,High);
		_delay_ms(1);
		DIO_VidWritePin(PINB2,Low);
	}
}


/*void WRITE_TempIN_SPDR(void)
{
	SPI_VoidSendNoBlock((u8)(TEMP/10));
}*/
//====================================================


//************************MASTER***********************  
static volatile MASTER_RECFROMSLAVE=0;

void EXFUN(void)
{
	MASTER_RECFROMSLAVE=1;
}

// WHEN PushButton Is pressed receive data from slave
void EXTINTERRUPTINIT(void)
{
	sei();
	ExternalInttruptwillbeActivatedWith(Interrupt_INT0,NegativeEdge);
	Ext_SetCallBack(Interrupt_INT0,&EXFUN);
	ExternalInterruptEnable(Interrupt_INT0);
}

void MASTER_ReceiveTemp(void)
{
	MASTER_RECFROMSLAVE=1;
}

// when slave send signal to external interrupt of master // set flag then master should receive data now.
void EXTINTERRUPTINIT1(void)
{
	sei();
	ExternalInttruptwillbeActivatedWith(Interrupt_INT1,PostiveEdge);
	Ext_SetCallBack(Interrupt_INT1,&MASTER_ReceiveTemp);
	ExternalInterruptEnable(Interrupt_INT1);
}


void MASTERSENDRECIVEDATAFROMTOSLAVE_Runnable(void)
{
	if(MASTER_RECFROMSLAVE==1)
	{
		u8 data='A';
		u8 Recdata=SPI_u8MasterSendReciveDataChar(data);
		LCDGoTo(1,0);
		LCD_WriteNumber(Recdata);
		data++;
		MASTER_RECFROMSLAVE==0;
	}
}
