
#include "DIO_Interafce.h"

const DIO_PinStatus_Type  pinsStatusArr[PINTOTAL]={
	
	INFREE,   /*PINA0    OUT*/
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT,  /*PINA7    OUT*/
	
	OUTPUT,  /*PINB0    OUT*/
	OUTPUT,
	OUTPUT,
	OUTPUT,
	INFREE,
	INFREE,
	OUTPUT,
	INFREE,  /*PINB7    OUT*/
	
	OUTPUT,  /*PINC0    OUT*/
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT,
	OUTPUT, /*PINC7    OUT*/
	
	INPULL, /*PIND0    OUT*/
	OUTPUT,
	INPULL,
	INPULL,
	OUTPUT,
	OUTPUT,
	INPULL,
	OUTPUT /*PIND7    OUT*/
};
