/*
 * dc_motor.c
 *
 *  Created on: Oct 10, 2023
 *      Author: dell
 */

#include "dc_motor.h"
#include "avr\io.h"








/*********************FUNCTIONS_DEFINTIONS**********************/


void DcMotor_Init(void)
{
	/*set DC_PINS DIRECTIONS AS OUTPUT */
	GPIO_setupPinDirection(DC_PORT_ID , DC_PIN0_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(DC_PORT_ID , DC_PIN1_ID , PIN_OUTPUT);

	/*stop motor at beginning*/
	GPIO_writePin(DC_PORT_ID , DC_PIN0_ID , LOGIC_LOW);
	GPIO_writePin(DC_PORT_ID , DC_PIN1_ID , LOGIC_LOW);


}

/************************************************/
void DcMotor_Rotate(DcMotor_State state)
{

	/* set DC_MOTOR DIRECTION*/
	if(state == STOP)
	{
		GPIO_writePin(DC_PORT_ID , DC_PIN0_ID , LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID , DC_PIN1_ID , LOGIC_LOW);
	}
	else if(state == ACW)
	{
		GPIO_writePin(DC_PORT_ID , DC_PIN0_ID , LOGIC_HIGH);
		GPIO_writePin(DC_PORT_ID , DC_PIN1_ID , LOGIC_LOW);

	}
	else if(state == CW)
	{
		GPIO_writePin(DC_PORT_ID , DC_PIN0_ID , LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID , DC_PIN1_ID , LOGIC_HIGH);
	}
	else
	{
		/*do nothing*/
	}




}
