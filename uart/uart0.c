#define GPA0CON		*((volatile unsigned int *)0xE0200000)
#define ULCON0		*((volatile unsigned int *)0xE2900000)
#define UCON0		*((volatile unsigned int *)0xE2900004)
#define UTRSTAT0	*((volatile unsigned int *)0xE2900010)
#define UTXH0		*((volatile unsigned int *)0xE2900020)
#define URXH0		*((volatile unsigned int *)0xE2900024)
#define UBRDIV0		*((volatile unsigned int *)0xE2900028)
#define UDIVSLOT0		*((volatile unsigned int *)0xE290002C)

void uart0_init(void)
{
	GPA0CON = 0x2222;
	ULCON0 = 0x3;
	UCON0 = 0x5;
	UBRDIV0 = 0x22;
	UDIVSLOT0 = 0xDDDD;

	return ;
}
char uart0_getchar(void)
{
	while (!(UTRSTAT0 & (1<<0)))
		;
	return URXH0;
}
void uart0_putchar(char ch)
{
	while (!(UTRSTAT0 & (1<<1)))
		;
	UTXH0 = ch;
	return ;
}
#if 1
void c_entry(void)
{
	char *ch;
	uart0_init();
	uart0_putchar('h');
	uart0_putchar('e');
	uart0_putchar('l');
	uart0_putchar('l');
	uart0_putchar('o');
	while (1)
	{
		//ch = uart0_getchar();
		//uart0_putchar(ch);
		mygets(ch);
		myputs(ch);
	}
	return ;
}
#endif
