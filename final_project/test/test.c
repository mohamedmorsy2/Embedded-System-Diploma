#include "timer1.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>
#include <util\delay.h>
#include "buzzer.h"








int main()
{
	Buzzer_init();


while(1)
{
	Buzzer_on();
	_delay_ms(1000);
	Buzzer_off();
	_delay_ms(1000);


}


return 0;
}
