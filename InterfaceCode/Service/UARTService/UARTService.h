/*
 * UARTService.h
 *
 * Created: 12/10/2022 4:47:18 PM
 *  Author: Admin
 */ 


#ifndef UARTSERVICE_H_
#define UARTSERVICE_H_

typedef enum
{
	
	FrameError=0,
	FrameOk=1

}UARTFRAME_ErrorType;

u32   UART_ReadNumber1(void);
u32   UART_ReadNumber(void);
void  UART_WriteNumber(u32 num);
void  UART_VoidReadString(u8 *str);
void  UART_VoidWriteString(char *str);
u8    CompareString(u8 *str1,u8 *str2);


#endif /* UARTSERVICE_H_ */