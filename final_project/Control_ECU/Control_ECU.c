#include <avr\io.h>
#include  <util\delay.h>
#include "lcd.h"
#include "uart.h"
# include "dc_motor.h"
# include "buzzer.h"
#include "external_eeprom.h"
#include "timer1.h"



/*    codes_used_in program to communicate between two microcontroller
 *       *  set pass
 *       #   door case
 *       $   change pass
 */

/*****************************************************************/
uint16  g_tick = 0;

/*function call in  the ISR of Timer 1*/
void tickk(void)
{
	g_tick++;
}

/*delay time function in second */
void delay_s (uint16 time)
{
	SREG |=(1<<7);

	while(g_tick != time);
	g_tick = 0;

	SREG &= !(1<<7);


}

/**********************************************************************/

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

/*check pass from EEPROM*/

uint8 check_pass_eeprom(uint8* pass1 , uint8 memory_ptr)
{
	uint8 i ;
	uint8 data =0;
	for(i=0 ; i<5 ; i++)
	{
		EEPROM_readByte(memory_ptr+i,&data);
		if(data != pass1[i])
		{
			return 0 ;
		}
	}

	return 1 ;
}

int main(void)

{

	uint8 pass1[5]={0};
	uint8 pass1_confirm[5]={0};

	uint8 data = 0;
	uint16 memory_ptr = 0x0000;  /* address of MEMORY in EEPROM */
	uint8 i ;
	uint8 command =0;



	/* set Configuration of Timer1
	 * every ISR = 1 second
	 * */
	Timer1_ConfigType timer_Config = {0 , 7813 ,clkI_1024 , CTC};
	Timer1_init(&timer_Config);
	Timer1_setCallBack(tickk);
	/*******************/
	/* set Configuration of USART*/
	USART_ConfigType uart_config = {asynch , disabled ,one_bit ,eight_bit ,9600};
	UART_init(&uart_config);

	LCD_init();


	DcMotor_Init();
	Buzzer_init();
	while(1)
	{
		command = UART_recieveByte();

		if(command == '*')
		{


			/*Initialize pass ARRAYS*/
			for(i=0 ; i<5 ; i++)
			{
				pass1[i] = 0;
				pass1_confirm[i] = 0;
			}


			/*Receive first password in pass1*/
			for(i=0 ; i<5 ; i++)
			{
				pass1[i] = UART_recieveByte();
			}

			/*Receive  password confirmation in pass1_confirm*/
			for(i=0 ; i<5 ; i++)
			{
				pass1_confirm[i] = UART_recieveByte();
			}
			/******store pass in EEPROM***********/
			if( check_pass(pass1 ,pass1_confirm ) )
			{

				for(i=0 ; i<5 ; i++)
				{
					EEPROM_writeByte(memory_ptr+i , pass1[i]);
					_delay_ms(10);

				}

			}
			/*send the result of the match of two password*/
			UART_sendByte (check_pass(pass1 ,pass1_confirm ));



			/*******************/
			LCD_clearScreen();

			for(i=0 ; i<5 ; i++)
			{
				EEPROM_readByte(memory_ptr+i,&data);
				LCD_intgerToString(data);
			}
			/*****************/
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
			if ( check_pass_eeprom(pass1_confirm ,memory_ptr) )
			{

				UART_sendByte (1);
				DcMotor_Rotate(CW);
				//_delay_ms(15000);
				delay_s(15);
				DcMotor_Rotate(STOP);
				//_delay_ms(3000);
				delay_s(3);
				DcMotor_Rotate(ACW);
				//_delay_ms(15000);
				delay_s(15);
				DcMotor_Rotate(STOP);
				//UART_sendByte (check_pass(pass1 ,pass1_confirm ));

			}
			else
			{

				UART_sendByte (0);
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
			if ( check_pass_eeprom(pass1_confirm ,memory_ptr) )
			{
				command = '*';
				UART_sendByte (1);

			}
			else
			{

				UART_sendByte (0);
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
