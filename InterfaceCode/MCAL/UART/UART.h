


#ifndef UART_H_
#define UART_H_

#include "STDTYPES.h"

void  UART_VoidInit(void);
void  UART_VoidWriteDataChar(u8 data);
u8    UART_U8ReadData(void);
u8    UART_ReadDataPeriodicCheck(u8 *pdata);
void  UART_RXComplete_InterruptEnable();
void  UART_RXComplete_InterruptDisable();
void  UART_TXComplete_InterruptEnable();
void  UART_TXComplete_InterruptDisable();
void  UART_SendByteNoBlock(u8 data);
u8    UART_ReceiveByteNoBlock(void);
void  UART_RXCIE_SetCallBack(void(*ptr)(void));
void  UART_TXCIE_SetCallBack(void(*ptr)(void));





#endif /* UART_H_ */