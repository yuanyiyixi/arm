#define GPA1CON		*((volatile unsigned int *)0xE0200020)
#define ULCON3		*((volatile unsigned int *)0xE2900C00)
#define UCON3		*((volatile unsigned int *)0xE2900C04)
#define UTRSTAT3	*((volatile unsigned int *)0xE2900C10)
#define UTXH3		*((volatile unsigned int *)0xE2900C20)
#define URXH3		*((volatile unsigned int *)0xE2900C24)
#define UBRDIV3		*((volatile unsigned int *)0xE2900C28)
#define UDIVSLOT3		*((volatile unsigned int *)0xE2900C2C)

void uart3_init(void)
{
	GPA1CON = 0x2222;
	ULCON3 = 0x3;
	UCON3 = 0x5;
	UBRDIV3 = 0x22;
	UDIVSLOT3 = 0xDDDD;

	return ;
}
char uart3_getchar(void)
{
	while (!(UTRSTAT3 & (1<<0)))
		;
	return URXH3;
}
void uart3_putchar(char ch)
{
	while (!(UTRSTAT3 & (1<<1)))
		;
	UTXH3 = ch;
	return ;
}
#if 0
void c_entry(void)
{
	char ch;
	uart0_init();
	uart3_init();
	uart3_putchar('h');
	uart3_putchar('e');
	uart3_putchar('l');
	uart3_putchar('l');
	uart3_putchar('o');
	while (1)
	{
		ch = uart0_getchar();
		uart3_putchar(ch);
	}
	return ;
}
#endif
