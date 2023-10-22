/*
 * ultrasonic.c
 *
 *  Created on: Oct 17, 2023
 *      Author: MOHAMED Morsy
 */


#include "ultrasonic.h"
#include "icu.h"
#include <util\delay.h>
#include <math.h>


uint8 g_tick=0;
uint16 g_time=0;

/*******************FUNCTION DEFINITION****************************************/



/******************************************************************************/



void Ultrasonic_init(void)
{
	ICU_ConfigType IcuConfig = {F_CPU_8 , RAISING};
	ICU_init(&IcuConfig);

	ICU_setCallBack(Ultrasonic_edgeProcessing);  /*send to ISR of icu*/
	GPIO_setupPinDirection(TRIGGER_PORT_ID ,TRIGGER_PIN_ID , PIN_OUTPUT);  /*TR PIN*/
	GPIO_writePin(TRIGGER_PORT_ID ,TRIGGER_PIN_ID , LOGIC_LOW );

}

/********************************************************************************/

void Ultrasonic_Trigger(void)
{

	GPIO_writePin(TRIGGER_PORT_ID ,TRIGGER_PIN_ID , LOGIC_HIGH );
	_delay_us(TRIGGER_PULSE);
	GPIO_writePin(TRIGGER_PORT_ID ,TRIGGER_PIN_ID , LOGIC_LOW );
}

/***********************************************************************************/
uint16 Ultrasonic_readDistance(void)
{
	uint16 distance =0;
	Ultrasonic_Trigger(); /*send TRIGGER PULSE*/

	/*speed = 340 m\s = 34000 cm/s
	 * speed/2 = 17000cm\s
	 * F(cpu) = 8Mhz , clock(icu) = 8
	 * F=8/8 = 1Mhz
	 * distance = 17000*10^-6 * g_time = (0.017*g_time) cm
	 *
	 * */

	distance = (float)0.017 *g_time ;

	return distance;

}

/************************************************************************/

void Ultrasonic_edgeProcessing(void)
{
	g_tick++;
	if(g_tick == 1)
	{

		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);

	}
	else if(g_tick == 2)
	{
		g_time = ICU_getInputCaptureValue();

		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RAISING);
		g_tick=0;
	}



}
