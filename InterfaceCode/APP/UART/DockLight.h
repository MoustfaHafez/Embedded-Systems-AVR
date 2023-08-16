
#ifndef DOCKLIGHT_H_
#define DOCKLIGHT_H_
#define size 4
typedef struct
{
	u8 *str,
	(*pf)(u8)
	
}UARTTASK_Type;


 void LEDOFFF(u8 num);
 void LEDONN(u8 num);
 static void MOTORON(u8 num);
 static void MOTOROFF(u8 num);
 void ReadMessagefromUART(void);
 void DisplayMessagefromUART(void);
 void SplitStringFromUARTintoStringAndNum(void);
 void DisplayStringMessageAndNumAfterSplitting(void);
 void CompareStringofUARTwithStringOfArr(void);
 void RestFlagAndNum(void);
 void UARTTASK_Runnable(void);
 

#endif