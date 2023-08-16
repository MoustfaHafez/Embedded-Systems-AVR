


#ifndef TX_RX_USING_INTERRUPT_H_
#define TX_RX_USING_INTERRUPT_H_
#define    F_CPU 8000000
#include  <util/delay.h>

void UART_RECIEVE_DATA_USING_Interrupt_Runnable();
void UART_USING_Interrupt_Init(void);
void FUN_RX(void);

///======================================================================

void FUN_TX(void);
void UART_SENDSTRING_Asyn_UsingInterrupt_Init();
u8 BusyFalgFun(void);
void UART_SENDSTRING_Asyn_UsingInterrupt_Runnable(u8 *str);


//======================================================================
void FUN_TX2(void);
void UART_SendData_Asynch_UsingInterrupt_TosetFlag_ThenSendData_inMainFun_Init(void);
void UART_SendData_Asynch_UsingInterrupt_TosetFlag_ThenSendData_inMainFun_Runnable(u8 *str);


//===========================================================================================
void UARTSTACK_RX(void);
void UARTPOP(void);
void UART_RECIEVEDATAUSINGSTACKSTRUCTURE_INIT(void);
void UART_USINGSTACKSTRUCTRUEUSINGBUTTONTOPOPDATA(void);
void UART_PUSH_POPDATAUSING_STACK_Runnable(void);

#endif /* TX_RX_USING_INTERRUPT_H_ */