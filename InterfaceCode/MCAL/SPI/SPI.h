/*
 * SPI.h
 *
 * Created: 12/23/2022 9:13:28 PM
 *  Author: Admin
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "STDTYPES.h"
#include "SPI_Cfg.h"

void SPI_VoidIntiMaster(void);
void SPI_VoidInitSlave(void);
u8   SPI_u8MasterSendReciveDataChar(u8 data);
u8   SPI_u8SlaveRecivedDataChar(u8 Data);
void SPI_VoidMasterSendString(u8 *str);
void SPI_VoidSendNoBlock(u8 data);
u8   SPI_U8RECIVENoBLOCK(void);

void SPI_InterruptEnable(void);
void SPI_interruptDisable(void);
void SPI_SETCALLBACK(void(*ptr)(void));

#endif /* SPI_H_ */