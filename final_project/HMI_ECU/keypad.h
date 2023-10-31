/*
 * name:mohamed morsy
 * file name :keypad.h
 * description: header file for keypad driver for AVR
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "std_types.h"


/**************DEFINITION**************/

   /*keypad configuration*/
#define KEYPAD_NUM_ROWS               4
#define KEYPAD_NUM_COLS               4

#define KEYPAD_ROW_PORT_ID          PORTA_ID
#define KEYPAD_FIRST_ROW_PIN_ID     PIN0_ID

#define KEYPAD_COL_PORT_ID          PORTA_ID
#define KEYPAD_FIRST_COL_PIN_ID      PIN4_ID

/*****keypad buttons connection**///

#define KEYPAD_BUTTON_PRESSED      LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED     LOGIC_HIGH
/***************function_prototype*********/
uint8 KEYPAD_getPressedKey(void);


#endif /* KEYPAD_H_ */
