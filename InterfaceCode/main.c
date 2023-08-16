

#include   "MemoryMap.h"
#include   "MacrosLikeFunction.h"
#include   "DIO.h"
#include   "DIO_Interafce.h"
#include   "STDTYPES.h"
#include   "Motor_Interface.h"
#include   "SevenSegment_Interface.h"
#include   "LCD_Interface.h"
#include   "KeyPad_Interface.h"
#include   "KeyPad_cfg.h"
#include   "Calculator.h"
#include   "Converter.h"
#include   "ADC.h"
#include   "Timer.h"
#include   "Sensors.h"
#include   "FireAlarm.h"
#include   "Interrupt.h"
#include   "TIMER_SERVICE.h"
#include   "Ultrasonic.h"
#include   "Boiler.h"
#include   "UARTService.h"
#include   "UART.h"
#include   "SPI.h"
#include   "DockLight.h"
#include   "TX_RX_USING_Interrupt.h"
#include   "I2C.h"





#define    F_CPU 8000000
#include  <util/delay.h>



#define secs 10;

#define StartStopButton    PINA0
#define CWCCWButton        PINA1
#define pushbutton         PINB0
#define psuhbutton2        PINB1
#define PB1                PIND2
#define PB2                PIND3
#define RED                PINC0
#define GREEN              PINC1
#define BLUE               PINC2
#define Buzer              PINC5
#define DummyData          0xff

/**************Recieve Data Using inteerupt*********************/

static u8 x= 0;

int main(void)
{
   u8 i=0,data;
  
   DIO_VidIntallPins();
   LCD_Init();
   KeyPad_Init();
   LCDGoTo(1,0);
   LCD_WriteString("Slave");
   ADCInit(VREF_VCC,ADC_SCALER_64); 
  // IWI_voidSlaveInit(0b11100000);
 
     
    while(1)
	{
	   // data=TWI_ReadACK();
		LCDGoTo(0,0);
		LCD_WriteChar(data);	
    }
 
 }















	