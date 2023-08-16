/*
 * UART.h
 *
 * Created: 1/4/2023 10:24:14 AM
 *  Author: Admin
 */ 


#ifndef UARTSTACK
#define UARTSTACK

typedef enum
{
	SATCKfULL,
	STACKEMPTY,
	STACKOK
	
}STACKSTATUS_Type;


STACKSTATUS_Type UART_PUSHBYTE(u8 data );
STACKSTATUS_Type UART_POPBYTE(u8 *  data);


#endif /* UART_H_ */