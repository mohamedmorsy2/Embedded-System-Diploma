/*
 * timer0.c
 *
 *  Created on: Oct 10, 2023
 *      Author: dell
 */

#include "timer0.h"
#include <avr\io.h>








/*function DEFINITION****/

void PWM_Timer0_Start(uint8 duty_cycle)
{
	/*Setup the PWM mode with Non-Inverting.
      Setup the prescaler with F_CPU/8*/
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);


	TCNT0 = 0;
	OCR0 = duty_cycle ;

	DDRB  = DDRB | (1<<PB3); //set PB3/OC0 as output pin*/

}

void PWM_Timer0_Duty_cycle(uint8 duty_cycle)
{
	TCNT0 = 0;
		OCR0 = duty_cycle ;

}
