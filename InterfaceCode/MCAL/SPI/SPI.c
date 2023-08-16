
#include "STDTYPES.h"
#include "MemoryMap.h"
#include "MacrosLikeFunction.h"
#include "SPI.h"

static void(*SPIPTR)(void)=0;

void SPI_VoidIntiMaster(void)
{
	/*Data order configuration   default MSB*/
	/*Enable master*/
	SETBIT(SPCR,MSTR);
	/*set clock fosc/16*/
	SETBIT(SPCR,SPR0);
	/*Enable SPI module*/
	SETBIT(SPCR,SPE);
	/******configure DIO PINS as output******/
	SETBIT(PORTB,4);
}

void SPI_VoidInitSlave(void)
{
	/************Data order configuration default MSB**************/
	/*************   default slave ********************************/
	/***************Enable SPI Module*****************************/
	SETBIT(SPCR,SPE);
	/**********************configure DIO PIns)*/
	
}

u8 SPI_u8MasterSendReciveDataChar(u8 data)
{
	
	RESETBIT(PORTB,4);// slave
	SPDR=data;
	while(ReadPin(SPSR,SPIF)==0);//data is transmitted
	return SPDR;
}

u8 SPI_u8SlaveRecivedDataChar(u8 Data)
{
	/**************Put may be Dummy Data in SPDR****************/
	SPDR=Data;
	while(ReadPin(SPSR,SPIF)==0)
	return SPDR;
}

void SPI_VoidMasterSendString(u8 *str)
{
	for(int i=0;str[i];i++)
	{
		SPI_u8MasterSendReciveDataChar(str[i]);
	}
}

void SPI_VoidSendNoBlock(u8 data)
{
	SPDR=data;
}

u8 SPI_U8RECIVENoBLOCK(void)
{
	return SPDR;
}

void SPI_InterruptEnable(void)
{
	SETBIT(SPSR,SPIF);
}

void SPI_interruptDisable(void)
{
	RESETBIT(SPSR,SPIF);
}

void SPI_SETCALLBACK(void(*ptr)(void))
{
	SPIPTR=ptr;
}

ISR(SPI_STC_vect)
{
	if(SPIPTR!=0)
	{
		SPIPTR();
	}
}