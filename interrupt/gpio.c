#define GPJ2CON *((volatile unsigned int *)0xe0200280)
#define GPJ2DAT *((volatile unsigned int *)0xe0200284)
#define GPD0CON *((volatile unsigned int *)0xe02000a0)
#define GPD0DAT *((volatile unsigned int *)0xe02000a4)
#define GPH2CON *((volatile unsigned int *)0xe0200c40)
#define GPH2DAT *((volatile unsigned int *)0xe0200c44)

void led_init(void)
{
	GPJ2CON &= 0xffff0000;
	GPJ2CON |= 0x1111;
	GPJ2DAT |= 0xf;
}
void led_on(int num)
{
	GPJ2DAT &= ~(1<<(num-1));
}
void led_off(int num)
{
	GPJ2DAT |= 1<<(num-1);
}
void buzzer_init(void)
{
	GPD0CON &= 0xfffffff0;
	GPD0CON |= 0x1;
	GPD0DAT &= 0xe;
}
void buzzer_on(void)
{
	GPD0DAT |= 0x1;
}
void buzzer_off(void)
{
	GPD0DAT &= 0xe;
}
void k1_init(void)
{
	GPH2CON &= 0xfffffff0; 
}
int k1_is_down(void)
{
	if (GPH2DAT & 1)
	return 0;
	else 
	return 1;
}
void k_init(void)
{
	GPH2CON &= 0x0;
}
int k_is_down(int num)
{	
	if (GPH2DAT & (1<<(num-1)))
	return 0;
	else 
	return 1;
}
