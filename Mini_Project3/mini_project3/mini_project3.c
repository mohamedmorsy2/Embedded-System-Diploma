#include <avr\io.h>
#include "std_types.h"
#include "lcd.h"
#include "adc.h"
#include "lm35_sensor.h"
#include "timer0.h"
#include "dc_motor.h"




int main (void)

{
	ADC_ConfigType adc_config = {INTERNAL , pr__8};   /*ADC CONFIGRATION*/
	SREG |= (1<<7); /*enable I_BIT*/

	/*drivers initialization */

	ADC_init(&adc_config);
	LCD_init();
	DcMotor_Init();
	PWM_Timer0_Start(255);
	uint8 temp =0;
	/*LCD*/
	LCD_displayString("temp =    c");
	LCD_moveCursor(1,0);
	LCD_displayString("DUTY =    %");



	while(1)
	{
		temp = LM35_getTemperature();

		/*display temperature*/
		if(temp >=100)
		{
			LCD_moveCursor(0,7);
			LCD_intgerToString(temp);

		}
		else
		{
			LCD_moveCursor(0,7);
			LCD_intgerToString(temp);
			LCD_displayString(" ");
		}

		/*temperature cases*/

		if(temp >= 120)
		{
			DcMotor_Rotate(CW ,100);
			LCD_moveCursor(1,7);
			LCD_intgerToString(100);


		}
		else if (temp >= 90 &&  temp<120 )
		{
			DcMotor_Rotate(CW ,75);
			LCD_moveCursor(1,7);
						LCD_intgerToString(75);
						LCD_displayString(" ");
		}
		else if (temp >= 60 &&  temp<90 )
		{
			DcMotor_Rotate(CW ,50);
			LCD_moveCursor(1,7);
						LCD_intgerToString(50);
						LCD_displayString(" ");
		}
		else if (temp >= 30 &&  temp<60 )
		{
			DcMotor_Rotate(CW ,25);
			LCD_moveCursor(1,7);
						LCD_intgerToString(25);
						LCD_displayString(" ");
		}
		else
		{
			DcMotor_Rotate(STOP ,0);
			LCD_moveCursor(1,7);
			LCD_intgerToString(0);
			LCD_displayString("  ");
		}



	}


	return 0;
}
