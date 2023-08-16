
#include "MemoryMap.h"
#include "STDTYPES.h"
#include "MacrosLikeFunction.h"
#include "I2C.h"


void TWI_voidMasterInit(void)
{	
	RESETBIT(TWSR,TWPS0);
	RESETBIT(TWSR,TWPS1);
	TWBR=12;                    // to scl =200 khz
    SETBIT(TWCR,TWEA);         //enable ack
	SETBIT(TWCR,TWEN);        //enable I2C	
}

void IWI_voidSlaveInit(u8 SlaveAddress)
{
	SETBIT(TWCR,TWEA);
	SETBIT(TWCR,TWEN); 	
	TWAR=SlaveAddress<<1;
}

TWI_ErrorStatus TWIMaster_EnumStartCondition(void)
{
	TWI_ErrorStatus ErrorState=TWI_OK;
	SETBIT(TWCR,TWINT);//clear flag
	SETBIT(TWCR,TWSTA);//Enable start condition
	while(ReadPin(TWCR,TWSTA)==0);//wait to check start condition ok
	if( TWSR &0xf8 !=0x08)
	{
		ErrorState=TWI_SC_Error;
	}
    RESETBIT(TWCR,TWSTA);
    return ErrorState;
}

TWI_ErrorStatus TWIMaster_EnumRepeatedStartCondition(void)
{
	TWI_ErrorStatus ErrorState=TWI_OK;
	SETBIT(TWCR,TWINT);
	SETBIT(TWCR,TWSTA);
	while(ReadPin(TWCR,TWINT)==0);
	if(TWSR&0xf8 !=0x10)
	{
		ErrorState=TWI_RESC_Error;
	}	
	RESETBIT(TWCR,TWSTA);	
    return ErrorState;
}
TWI_ErrorStatus TWIMaster_EnumStopCondition(void)
{
	TWI_ErrorStatus ErrorState=TWI_OK;
	SETBIT(TWCR,TWINT);
	SETBIT(TWCR,TWSTO);
	return ErrorState;
}

TWI_ErrorStatus TWIMaster_sendSlaveAddWithWriteMode(u8 slaveID)
{
	TWI_ErrorStatus ErrorState=TWI_OK;
	SETBIT(TWCR,TWINT);//clear flag
	TWDR=slaveID<<1;//Slave ID
	RESETBIT(TWDR,0);// Mode
	while(ReadPin(TWCR,TWINT)==0);//wait flag set to one
	if(TWSR &0xf8 !=0x18)
	{
		ErrorState =TWI_SLA_W_Error;
	}
	return ErrorState;	
}

TWI_ErrorStatus TWIMaster_sendSlaveAddWithReadMode(u8 slaveID)
{
	TWI_ErrorStatus ErrorState=TWI_OK;
	SETBIT(TWCR,TWINT);//clear flag
	TWDR=slaveID<<1;//Slave ID
	SETBIT(TWDR,0);// ReadMode
	while(ReadPin(TWCR,TWINT)==0);//wait flag set to one
	if(TWSR &0xf8 !=0x40)
	{
		ErrorState =TWI_SLA_R_Error;
	}
	return ErrorState;
}

TWI_ErrorStatus TWIMaster_sendDataToSlave(u8 Data)
{
	TWI_ErrorStatus ErrorState=TWI_OK;
	SETBIT(TWCR,TWINT);//clear flag
	TWDR=Data;
	while(ReadPin(TWCR,TWINT)==0);//wait flag set to one
	if(TWSR &0xf8 !=0x28)
	{
		ErrorState=TWI_MS_TT_Error;
	}
	return ErrorState;
}

TWI_ErrorStatus TWIMaster_ReadDataFromSlave(u8 *Data)
{
	TWI_ErrorStatus ErrorState=TWI_OK;
	SETBIT(TWCR,TWINT);//clear flag
	while(ReadPin(TWCR,TWINT)==0);//wait flag set to one
	if(TWSR &0xf8 !=0x50)
	{
		ErrorState=TWI_MS_RXDATA_Error;
	}
	else
	{
		*Data=TWDR;
	}
	return ErrorState;
}

u8 TWI_ReadACK(void)
{
	TWCR = (1 << TWINT) | (1<<TWEN) | (1<<TWEA) ; // Enable Ack
	//wait for TWINT Flag set in TWCR Register
	while(!(TWCR & ( 1 << TWINT )));
	//Read Data
	return TWDR ;
}










