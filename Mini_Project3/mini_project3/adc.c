/*
 * name:mohamed morsy
 * file name :adc.c
 * description: source file for adc driver for AVR
 */
#include "common_macros.h"
#include "adc.h"
#include "avr\io.h"



/***********DEFINTION**************/


void ADC_init(const ADC_ConfigType* Config_Ptr)
{

	/* ADMUX Register Bits Description:
	 *  * ADLAR   = 0 right adjusted
	 *   * MUX4:0  = 00000 to choose channel 0 as initialization
	 *   */

	ADMUX = 0;

	/*choose reference volt*/
	ADMUX = (ADMUX&0x3F) | ((Config_Ptr->ref_volt) << 6);



	ADCSRA = (ADCSRA & 0xF8) |  (Config_Ptr->prescaler)   ; /* choose prescaler*/

	ADCSRA |= (1<<ADEN) ; /* ADEN    = 1 Enable ADC*/


}


uint16 ADC_readChannel(uint8 channel_num)
{
    /* Input channel number must be from 0 --> 7 */
	/* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */

	ADMUX = (ADMUX &0xE0)  | (channel_num &0x07) ;
	ADCSRA |= (1<<ADSC);/* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA , ADIF)); /* Wait for conversion to complete, ADIF becomes '1'  (POLLING)*/
	SET_BIT(ADCSRA , ADIF);  /*clear flag*/
	return ADC ; /* Read the digital value from the data register */

}







