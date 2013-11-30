#include "gpio.h"

extern void do_irq(void);

static void delay(int sec)
{
	int i,j;
	for (i = 0; i < sec; i++)
		for (j = 0; j < 0xffff; j++)
			;
}
void func(void) 
{

	buzzer_on();
	delay(1);
	buzzer_off();
	return;
}
int test(void)
{
	int i = 0;
	led_init();
	buzzer_init();
	k1_init();
			irq_init(do_irq);
	while(1)
	{
			led_on(i%4 + 1);
			delay(1);
			led_off(i%4 + 1);
			delay(1);
			i++;
	}
	return 0;
}
