/*
 * LCD_Cfg.h
 *
 * Created: 11/8/2022 11:51:47 AM
 *  Author: Admin
 */ 


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define LCD_4Bit          1

#define LCDProteus        1
#define LCDkit            2
#define LCDDisplay        LCDProteus
 

#define LCDMODE         LCD_4Bit


/*****KIT CONFIGURATION******
#define   RS             PINA1
#define   LCDEN          PINA2  

#define   D7             PINA6
#define   D6             PINA5
#define   D5             PINA4
#define   D4             PINA3*/



/*Proteues configuration**/
#define   RS             PINB2
#define   LCDEN          PINB1

#define   D7             PINA7
#define   D6             PINA6
#define   D5             PINA5
#define   D4             PINA4



#define   LCDPORT         PA


#endif /* LCD_CFG_H_ */