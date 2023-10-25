#include  "lcd.h"
#include  "ultrasonic.h"
#include <util\delay.h>
#include <avr\io.h>








int main(void)
{
	uint16 distance=0;
	SREG |=(1<<7); /*enable I_BIt*/
	LCD_init();
	Ultrasonic_init();


	while(1)
	{
		distance = Ultrasonic_readDistance();

		LCD_clearScreen();
		LCD_intgerToString(distance);



		while(Ultrasonic_readDistance() == distance );


	}



	return 0;





}
