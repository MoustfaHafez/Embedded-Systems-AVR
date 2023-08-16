#ifndef DOCKLIGHT_H_
#define DOCKLIGHT_H_
#define size 2
typedef struct
{
	u8 *str,
	(*pf)(u8)
	
}UARTTASK_Type;


 void LEDOFFF(u8 num);
 void LEDONN(u8 num);
 void ReadMessagefromUART(void);
 void DisplayMessagefromUART(void);
 void SplitStringFromUARTintoStringAndNum(void);
 void DisplayStringMessageAndNumAfterSplitting(void);
 void CompareStringofUARTwithStringOfArr(void);
 void RestFlagAndNum(void);

#endif