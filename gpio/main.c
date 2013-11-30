#include "gpio.h"
static void delay(int sec)
{
	int i,j;
	for (i = 0; i < sec; i++)
		for (j = 0; j < 0xfffff; j++)
		;
}
int test(void)
{
	int i = 0;
	led_init();
	buzzer_init();
	k1_init();
	while(1)
	{
		if(k1_is_down())
		{
		buzzer_on();
		led_on(i%4 + 1);
		delay(1);
		buzzer_off();
		led_off(i%4 + 1);
		delay(1);
		i++;
		}
	}
	return 0;
}
