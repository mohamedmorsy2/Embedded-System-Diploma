
/*
 * name:mohamed morsy
 * file name :lcd.c
 * description: source file for lcd driver for AVR
 */

#include "common_macros.h"
#include "gpio.h"
#include "lcd.h"
#include <util/delay.h>


/****************    Functions Definitions *******************/

void LCD_init(void)
{
	/*set direction of screen pins*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT); /*LCD RS*/
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);  /*LCD E*/
	_delay_ms(20);		/* LCD Power ON delay always > 15ms */
#if(LCD_DATA_BITS_MODE == 4)

	/*set DATA FOUR BIT DIRECTION*/
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID , PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

		/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
		LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(LCD_DATA_PORT_ID ,PORT_OUTPUT);  /*data port*/
	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif


	/*5*7 dot display Mode */
	LCD_sendCommand(LCD_CURSOR_OFF); /* cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */

}

/**********************************************************************/


void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID, LOGIC_LOW);   /* write zero to RS pin to send instruction*/
	_delay_ms(1);  /* tas = 50 nsec*/

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID, LOGIC_HIGH );   /* write 1 to enable pin*/
	_delay_ms(1);  /* Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)


	                         /*first send MB BITS**/
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB4_PIN_ID , GET_BIT(command,4) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB5_PIN_ID , GET_BIT(command,5) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB6_PIN_ID , GET_BIT(command,6) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB7_PIN_ID , GET_BIT(command,7) );

	_delay_ms(1);  /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable screen*/
	_delay_ms(1); /*  Th = 13ns */

	                  /*second send LB BITS*/
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID, LOGIC_HIGH );   /*  enable E pin*/
	_delay_ms(1);  /* Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB4_PIN_ID , GET_BIT(command,0) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB5_PIN_ID , GET_BIT(command,1) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB6_PIN_ID , GET_BIT(command,2) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB7_PIN_ID , GET_BIT(command,3) );

	_delay_ms(1);  /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable screen*/
	_delay_ms(1); /*  Th = 13ns */


#elif(LCD_DATA_BITS_MODE ==8 )

	GPIO_writePort(LCD_DATA_PORT_ID,command);   /*send command to screen*/
	_delay_ms(1);  /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable screen*/
	_delay_ms(1); /*  Th = 13ns */
#endif

}

/**********************************************************************/


void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID, LOGIC_HIGH);   /* write 1 to RS pin to send DATA*/
	_delay_ms(1);  /* tas = 50 nsec*/

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID, LOGIC_HIGH );   /* write 1 to  E enable pin*/
	_delay_ms(1);  /* Tpw - Tdws = 190ns */

#if(LCD_DATA_BITS_MODE == 4)


	/*first send MB BITS**/
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB4_PIN_ID , GET_BIT(character,4) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB5_PIN_ID , GET_BIT(character,5) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB6_PIN_ID , GET_BIT(character,6) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB7_PIN_ID , GET_BIT(character,7) );
	_delay_ms(1);  /* delay for processing Tdsw = 100ns */

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable  E PIN of screen*/
	_delay_ms(1); /*  Th = 13ns */

	/*second send LB BITS*/
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID, LOGIC_HIGH );   /*  enable E pin*/
		_delay_ms(1);  /* Tpw - Tdws = 190ns */


	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB4_PIN_ID , GET_BIT(character,0) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB5_PIN_ID , GET_BIT(character,1) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB6_PIN_ID , GET_BIT(character,2) );
	GPIO_writePin(LCD_DATA_PORT_ID,  LCD_DB7_PIN_ID , GET_BIT(character,3) );

	_delay_ms(1);  /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable screen*/
	_delay_ms(1); /*  Th = 13ns */


#elif(LCD_DATA_BITS_MODE ==8 )

	GPIO_writePort(LCD_DATA_PORT_ID,character);   /*send command to screen*/
	_delay_ms(1);  /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable screen*/
	_delay_ms(1); /*  Th = 13ns */
#endif


}

/**********************************************************************/

void LCD_displayString(const char *Str)
{
	uint32 i=0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}

}

/**********************************************************************/


void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;
	switch(row)
	{
	case 0 : lcd_memory_address= col;break;
	case 1:  lcd_memory_address= col+0x40;break;
	case 2:  lcd_memory_address= col+0x10;break;
	case 3:  lcd_memory_address= col+0x50;break;


	}

	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);  /*address of cursor the MSB always be 1*/
	/*so thats why we made address or with 0x80*/


}

/**********************************************************************/

void LCD_displayStringRowColumn(uint8 row , uint8 col,const char *str)
{
	LCD_moveCursor(row,col);  /*required position*/
	LCD_displayString(str);  /*display string/*/

}
/**********************************************************************/

void LCD_intgerToString(int data)
{
	char buff[16];
	itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	LCD_displayString(buff);
}

/**********************************************************************/
void LCD_floatToString(float32 value)
{
	uint32 intg = 	value;
	float32 dd = (value - intg)*100;
	LCD_intgerToString(intg);
	LCD_displayString(".");
	LCD_intgerToString(dd);
}

/**********************************************************************/
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}




