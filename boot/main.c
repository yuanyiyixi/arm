#include "gpio.h"
#include "lib.h"
#include "uart.h"
int c_entry(void)
{
	button_init();
	led_init();
	uart0_init();
	while(1)
	{
		if (button_is_down())
			loader_OS();
		else 
			myshell();
	}
	return 0;
}
