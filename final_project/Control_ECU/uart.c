/*
 ***********************************************************************
 *
 *Author: Mohamed Morsy
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 */

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */


/*****Function DEFINITIONS**************/


void UART_init(const USART_ConfigType* Config_Ptr )
{
	uint16 ubrr_value =0;
	UCSRA = (1<<U2X) ;   /* Double the USART Transmission Speed*/

	UCSRB = (1<<RXEN) | (1<<TXEN);  /* enable UART*/

	UCSRB = (UCSRB&0xFB) | ((Config_Ptr->datasize) & 0x4) ;  /*  UCSZ2 for data size*/

	UCSRC |= (1<<URSEL); /* to select UCSRC register*/

	UCSRC = (UCSRC & 0xBF) | ((Config_Ptr->mode) << 6);  /* to select USART MODE*/

	UCSRC = (UCSRC & 0xCF) | ((Config_Ptr->parity)  << 4); /*Parity Mode*/

	UCSRC = (UCSRC & 0xF7) | ((Config_Ptr->stopbit)  << 3); /* stop bit*/

	UCSRC = (UCSRC & 0xF9) | (( (Config_Ptr->datasize)& 0x3) <<1) ; /* for data size*/

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / ((Config_Ptr->baud_rate) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}
/***********************************************************************************************/

void UART_sendByte(const uint8 data)

{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}  /* wait until transmit is complete*/
	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

}
/*************************************************************************************************/

uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;

}
/*******************************************************************************************/
void UART_sendString(const uint8 *Str)
{
	uint16 i =0;
while(Str[i] != '\0')
{
	UART_sendByte(Str[i]);
	i++;
}

}

/*******************************************************************************************/
void UART_receiveString(uint8 *Str)
{

	uint8 i = 0;

		/* Receive the first byte */
		Str[i] = UART_recieveByte();

		/* Receive the whole string until the '#' */
		while(Str[i] != '#')
		{
			i++;
			Str[i] = UART_recieveByte();
		}

		/* After receiving the whole string plus the '#', replace the '#' with '\0' */
		Str[i] = '\0';


}
