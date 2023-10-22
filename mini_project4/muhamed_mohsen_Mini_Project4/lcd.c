
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
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	GPIO_setupPortDirection(LCD_DATA_PORT_ID ,PORT_OUTPUT);  /*data port*/

	_delay_ms(20);		/* LCD Power ON delay always > 15ms */

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
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
	GPIO_writePort(LCD_DATA_PORT_ID,command);   /*send command to screen*/
	_delay_ms(1);  /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable screen*/
	_delay_ms(1); /*  Th = 13ns */

}

/**********************************************************************/


void LCD_displayCharacter(uint8 character)
{
	GPIO_writePin(LCD_RS_PORT_ID , LCD_RS_PIN_ID, LOGIC_HIGH);   /* write zero to RS pin to send data*/
	_delay_ms(1);  /* tas = 50 nsec*/

	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID, LOGIC_HIGH );   /* write 1 to enable pin*/
	_delay_ms(1);  /* Tpw - Tdws = 190ns */
	GPIO_writePort(LCD_DATA_PORT_ID,character);   /*send command to screen*/
	_delay_ms(1);  /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);  /*disable screen*/
	_delay_ms(1); /*  Th = 13ns */

}

/**********************************************************************/

void LCD_displayString(uint8*str)
{
	uint32 i=0;
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}

}

/**********************************************************************/


void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address =0x00;
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

void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}




