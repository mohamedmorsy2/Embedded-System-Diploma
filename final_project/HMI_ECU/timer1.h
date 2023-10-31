/*
 * NAME : Mohamed MORSY
 * Description :  header file for timer 1 that support normal and compare mode
 *
 *  Created on: Oct 24, 2023
 *      Author: dell
 */

#ifndef TIMER1_H_
#define TIMER1_H_


#include "std_types.h"
/*********************DEFINITIONS********************************************************/

typedef enum
{
	Normal , CTC

}Timer1_Mode;

typedef enum
{
	No_clock_source , clkI_1 , clkI_8, clkI_64, clkI_256, clkI_1024

}Timer1_Prescaler;


typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;
} Timer1_ConfigType;


/***********************FUNCTION_DEFINTION**************************************/


/*Function to initialize the Timer driver*/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/* Function to disable the Timer1 */
void Timer1_deInit(void);

/*Function to set the Call Back function address*/
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
