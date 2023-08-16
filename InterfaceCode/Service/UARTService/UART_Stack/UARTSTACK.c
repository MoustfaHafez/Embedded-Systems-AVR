
#include "STDTYPES.h"
#include "UARTSTACK.h"
#define STACKSIZE 5

static u8 index=0;
static u8 UARTBUFEER[ STACKSIZE];

STACKSTATUS_Type UART_PUSHBYTE(u8 data )
{
	if(index== STACKSIZE)
	{
		return SATCKfULL;
	}
	else
	{
		UARTBUFEER[index]=data;
		index++;
		return STACKOK;
	}
}

STACKSTATUS_Type UART_POPBYTE(u8 *  data)
{
	if(index==0)
	{
		return STACKEMPTY;
	}
	else
	{
		index--;
	    *data=UARTBUFEER[index];
	    return STACKOK;
		
	}
}