/*
***********************************************************************
 *
 *Author: Mohamed Morsy
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 *
 *
 ******************************************************************************
 *****************************************************************************/


#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/******************************DEFINITIONS******************/


typedef enum
{
	asynch , synch

}USART_ModeSelect;

typedef enum
{
	disabled , reserved , even , odd
}USART_ParityMode;

typedef enum
{
one_bit ,two_bit

}USART_StopBit;

typedef enum
{
five_bit , six_bit , seven_bit , eight_bit , nine_bit=7

}USART_CharacterSize;


typedef struct
{
	USART_ModeSelect mode;
	USART_ParityMode parity;
	USART_StopBit stopbit;
	USART_CharacterSize datasize;
	uint32 baud_rate;


}USART_ConfigType;




/*************FUNCTION PROTOTYPES****************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

void UART_init(const USART_ConfigType* Config_Ptr );

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #






#endif /* UART_H_ */
