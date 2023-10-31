#include <avr\io.h>
#include  <util\delay.h>
#include "lcd.h"
#include "uart.h"
# include "dc_motor.h"
# include "buzzer.h"


/*    codes_used_in program to communicate between two microcontroller
 *       *  set pass
 *       #   door case
 *       $   change pass
 */



/* function to compare between to passwords
 * return 1 if they match
 * else return 0
 * */
uint8 check_pass(uint8* pass1  , uint8* pass1_confirm)
{
	uint8 i;
	for(i=0 ; i<5 ; i++)
	{
		if(pass1[i]  != pass1_confirm[i] )
		{
			return 0;
		}
	}
	return 1 ;

}

int main(void)
{

	USART_ConfigType uart_config = {asynch , disabled ,one_bit ,eight_bit ,9600};
	LCD_init();

	UART_init(&uart_config);
	uint8 pass1[5]={0};
	uint8 pass1_confirm[5]={0};
	uint8 i ;
	uint8 command =0;
	DcMotor_Init();
	Buzzer_init();
	while(1)
	{
		command = UART_recieveByte();

		if(command == '*')
		{


			/*Initialize pass*/
			for(i=0 ; i<5 ; i++)
			{
				pass1[i] = 0;
				pass1_confirm[i] = 0;
			}


			/*Receive first password*/
			for(i=0 ; i<5 ; i++)
			{
				pass1[i] = UART_recieveByte();
			}

			/*Receive  password confirmation*/
			for(i=0 ; i<5 ; i++)
			{
				pass1_confirm[i] = UART_recieveByte();
			}
			/*send the result of the match of two password*/
			UART_sendByte (check_pass(pass1 ,pass1_confirm ));



			/*******************/
			LCD_clearScreen();
			for(i=0 ; i<5 ; i++)
			{
				LCD_intgerToString(pass1[i]);
			}
			LCD_moveCursor(1,0);

			for(i=0 ; i<5 ; i++)
			{
				LCD_intgerToString(pass1_confirm[i]);
			}

			command=0;

		}
		/*********************************************************/
		/*door case*/
		else if(command == '#')
		{
			/*intialize pass1*/

			for(i=0 ; i<5 ; i++)
			{
				pass1_confirm[i] = 0;
			}

			/*Receive pass*/
			for(i=0 ; i<5 ; i++)
			{
				pass1_confirm[i] = UART_recieveByte();
			}
			/*check pass*/
			if ( check_pass(pass1 ,pass1_confirm) )
			{

				UART_sendByte (check_pass(pass1 ,pass1_confirm ));
				DcMotor_Rotate(CW,100);
				_delay_ms(1000);
				DcMotor_Rotate(STOP,100);
				_delay_ms(2000);
				DcMotor_Rotate(ACW,100);
				_delay_ms(1000);
				DcMotor_Rotate(STOP,100);
				//UART_sendByte (check_pass(pass1 ,pass1_confirm ));

			}
			else
			{

				UART_sendByte (check_pass(pass1 ,pass1_confirm ));
			}
			command = 0;


		}
		/**************************************/

		else if (command == '$')
		{
			/*intialize pass1*/

			for(i=0 ; i<5 ; i++)
			{
				pass1_confirm[i] = 0;
			}

			/*Receive pass*/
			for(i=0 ; i<5 ; i++)
			{
				pass1_confirm[i] = UART_recieveByte();
			}
			_delay_ms(10);
			/*check pass*/
			if ( check_pass(pass1 ,pass1_confirm) )
			{
				command = '*';
				UART_sendByte (check_pass(pass1 ,pass1_confirm ));

			}
			else
			{

				UART_sendByte (check_pass(pass1 ,pass1_confirm ));
			}

		}
		/****ERROR CASE******/
		else if(command == 'E')
		{

			Buzzer_on();
			_delay_ms(1000);
			Buzzer_off();
			command = 0;
		}



	}









	return 0 ;
}
