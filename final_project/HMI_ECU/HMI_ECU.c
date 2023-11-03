#include <avr\io.h>
#include  <util\delay.h>
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer1.h"



/*    codes_used_in program to communicate between two microcontroller
 *       *  set pass
 *       #   door case
 *       $   change pass
 */

/**********************/
 uint16  g_tick = 0;
void tickk(void)
{
	g_tick++;
}

void delay (uint16 time)
{
	SREG |=(1<<7);

	while(g_tick != time);
	g_tick = 0;

	SREG &= !(1<<7);


}

/**************************/



int main(void)
{

	/******************/


		Timer1_ConfigType timer_Config = {0 , 7813 ,clkI_1024 , CTC};
		Timer1_init(&timer_Config);
		Timer1_setCallBack(tickk);
		/*******************/

	uint8 data,condition  ;
	USART_ConfigType uart_config = {asynch , disabled ,one_bit ,eight_bit ,9600};
	LCD_init();

	UART_init(&uart_config);
	LCD_displayString("plz enter pass :");
	int pass1[5]={0};
	int pass1_confirm[5]={0};
	int i,pass_check=0 ;
	int door_pass=0 , change_pass =0 ;
	int error=0; /* for error*/


	while(1)
	{


		/******************************** FIRST OPTION TO SET PASSWORD********************************************/

		while(pass_check == 0)
		{
			UART_sendByte('*');  /*set password*/
			/* Initialize arrays*/
			for(i=0 ; i<5 ; i++)
			{

				pass1[i] = 0;

			}
			i=0;
			//UART_sendByte('*');  /*set password*/

			LCD_clearScreen();

			LCD_displayString("plz enter pass :");

			_delay_ms(600);


			data = KEYPAD_getPressedKey();



			/*first time enter pass of size 5 and display and store it in array*/
			while(data != '=')
			{
				if (i==5)
				{
					/* do nothing*/
				}

				else if (data != '=')
				{
					LCD_intgerToString(data);
					LCD_moveCursor(1,i);
					_delay_ms(250);
					LCD_displayCharacter('*');
					pass1[i] = data;
					_delay_ms(600);
					i++;
				}
				data = KEYPAD_getPressedKey();
				_delay_ms(600);
			}

			/* send pass to MC */

			for(i=0 ; i<5 ; i++)
			{
				UART_sendByte(pass1[i]);
			}

			/*RE_enter PASS*/
			LCD_clearScreen();
			LCD_displayString("plz re_enter pass :");
			LCD_moveCursor(1,0);

			/* Initialize arrays*/
			for(i=0 ; i<5 ; i++)
			{

				pass1[i] = 0;

			}
			i=0;
			data = KEYPAD_getPressedKey();



			/*re_enter Password */
			while(data != '=')
			{
				if (i==5)
				{
					/* do nothinf*/
				}

				else if (data != '=')
				{
					LCD_intgerToString(data);
					LCD_moveCursor(1,i);
					_delay_ms(250);
					LCD_displayCharacter('*');
					pass1[i] = data;
					_delay_ms(600);
					i++;
				}
				data = KEYPAD_getPressedKey();
				_delay_ms(600);
			}

			//_delay_ms(600);

			/*send re_pass TO MC*/
			for(i=0 ; i<5 ; i++)
			{
				UART_sendByte(pass1[i]);
			}

			pass_check =UART_recieveByte();  /* result of password checking*/

		}
		/******************************** MAIN OPTIONS********************************************/

		while(pass_check == 1)
		{
			LCD_moveCursor(0,0);

			LCD_clearScreen();
			LCD_displayString("+ : open door");
			LCD_moveCursor(1,0);
			LCD_displayString("- : change pass");
			_delay_ms(600);
			condition = KEYPAD_getPressedKey();


			/************open door CASE********************/

			if(condition == '+' )
			{
				while(door_pass == 0)
				{
					UART_sendByte('#');  /*door code send to MC*/
					LCD_clearScreen();
					LCD_displayString("enter password");
					_delay_ms(600);
					data = KEYPAD_getPressedKey();
					/* Initialize arrays*/
					for(i=0 ; i<5 ; i++)
					{

						pass1[i] = 0;

					}
					i=0;
					//LCD_moveCursor(1,i);
					while(data != '=')
					{
						if (i==5)
						{
							/* do nothinf*/
						}

						else if (data != '=')
						{
							LCD_moveCursor(1,i);
							LCD_intgerToString(data);
							LCD_moveCursor(1,i);
							_delay_ms(250);
							LCD_displayCharacter('*');
							pass1[i] = data;
							_delay_ms(600);
							i++;
						}
						data = KEYPAD_getPressedKey();
						_delay_ms(600);
					}
					/*send pass to MC*/
					for(i=0 ; i<5 ; i++)
					{
						UART_sendByte(pass1[i]);
					}
					door_pass = UART_recieveByte(); /* receive pass checking result*/
					if(door_pass)
					{
						LCD_clearScreen();
						LCD_displayString("door is unlocking");
						//_delay_ms(15000);
						delay(15);
						LCD_clearScreen();
						LCD_displayString("door is open");
						//_delay_ms(3000);
						delay(3);

						LCD_clearScreen();
						LCD_displayString("door is Locking");
						//_delay_ms(15000);
						delay(15);






					}

					/*if(door_pass)
					{

					}*/
					error++;
					/******in case of error send 'E' to MC******/
					if(error==3)
					{
						UART_sendByte('E');   /* send 'E' to MC*/
						LCD_clearScreen();
						LCD_displayString("error");
						door_pass=1;
						_delay_ms(1000);
					}


				}


				door_pass = 0;  /* to go in  while loop of door_case  again*/
				error=0;
				condition=0;

			}
			/******************change_pass CASE *******************/
			else if(condition == '-' )
			{


				while(change_pass == 0)
				{


					/* Initialize arrays*/
					for(i=0 ; i<5 ; i++)
					{

						pass1[i] = 0;
					}

					UART_sendByte('$');  /*change_password code send to MC*/
					LCD_clearScreen();
					LCD_displayString("enter password");
					_delay_ms(600);
					data = KEYPAD_getPressedKey();
					/* Initialize arrays*/

					i=0;
					//LCD_moveCursor(1,i);
					while(data != '=')
					{
						if (i==5)
						{
							/* do nothinf*/
						}

						else if (data != '=')
						{
							LCD_moveCursor(1,i);
							LCD_intgerToString(data);
							LCD_moveCursor(1,i);
							_delay_ms(250);
							LCD_displayCharacter('*');
							pass1[i] = data;
							_delay_ms(600);
							i++;
						}
						data = KEYPAD_getPressedKey();
						_delay_ms(600);
					}

					/*send pass to MC*/
					for(i=0 ; i<5 ; i++)
					{
						UART_sendByte(pass1[i]);
					}
					_delay_ms(10);
					change_pass = UART_recieveByte(); /* receive pass_checking result from MC*/

					error++;

					/******in case of error send 'E' to MC******/
					if(error==3)
					{
						UART_sendByte('E');
						LCD_clearScreen();
						LCD_displayString("error");
						change_pass=1;
						_delay_ms(1000);

					}

				}

				change_pass = 0;   /* to go in  while loop of change_case  again*/
				if(error ==3)
				{
				}
				else
				{
					pass_check=0;
				}
				change_pass=0;
				error=0;
				condition=0;
			}


		}

		_delay_ms(600);



	}


	return 0 ;
}
