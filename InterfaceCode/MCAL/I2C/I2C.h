


#ifndef I2C_H_
#define I2C_H_

typedef enum
{
	TWI_OK=1,
	TWI_SC_Error,
	TWI_STC_Error,
	TWI_RESC_Error,
	TWI_SLA_W_Error,
	TWI_SLA_R_Error,
	TWI_MS_TT_Error,
	TWI_MS_RXDATA_Error
}TWI_ErrorStatus;
typedef enum
{
	StartConditionDone=0x08,
	RepeatedStartConditionDone=0x10,
}StatusCode_Type;

void TWI_voidMasterInit(void);




#endif 