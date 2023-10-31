/*
 * NAME : Mohamed MORSY
 * Description :  source file for  BUZZER driver
 *
 *  Created on: Oct 25, 2023
 *
 */


#include  "buzzer.h"




/********************FUNCTION_DEFENITION******************/


/*Description
⮚ Setup the direction for the buzzer pin as output pin through the
GPIO driver.
⮚ Turn off the buzzer through the GPIO.*/

void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN_ID , PIN_OUTPUT);  /* set pin as output*/
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);    /* turn off BUZZER*/

}

/*Description
⮚ Function to enable the Buzzer through the GPIO.*/


void Buzzer_on(void)
{

	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_HIGH);/* turn ON BUZZER*/

}

/*Function to disable the Buzzer through the GPIO*/

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);    /* turn off BUZZER*/
}


