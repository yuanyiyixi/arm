
#include "uart.h"

void putchar_hex(char c)
{
	char * hex = "0123456789ABCDEF";

	uart0_putchar(hex[(c>>4) & 0x0F]);
	uart0_putchar(hex[(c>>0) & 0x0F]);

	return;
}

void myputchar(char c)
{
	// '\n' -> '\r' + '\n'
	if (c == '\n')
		uart0_putchar('\r');
	else if(c == 0x7f)
	{
		uart0_putchar('\b');
		uart0_putchar(' ');
		uart0_putchar('\b');
		return ;
	}
	uart0_putchar(c);
}

void putint_hex(int n)
{
	putchar_hex((n>>24) & 0xFF);
	putchar_hex((n>>16) & 0xFF);
	putchar_hex((n>>8) & 0xFF);
	putchar_hex((n>>0) & 0xFF);
	uart0_putchar(' ');

	return;
}

int myputs(const char * s)
{
	const char * p = s;

	while (*p)
		myputchar(*p++);
	return (p - s);
}
char * mygets(char *s)
{
	char ch;
	char *p = s;
	while((ch = uart0_getchar()) != '\r')
	{
		if (p < s || (ch != 0x7f && p == s))
			myputchar(ch);
		if (ch == 0x7f)
		{
			if(p < s)
				s--;
			else
				s = p;
		}
		else 
		{
			*s = ch;
			s++;
		}
	}
	*s++ = '\r';
	*s++ = '\n';
	*s = '\0';
	return s;
}

int strlen(const char * s)
{
	const char * p = s;

	while (*p && (*p != '\r'))
		p++;

	return (p - s);
}

char * reverse(char * s)
{
	static int counter = 1;
	static char * p;	
	char save;

	if (counter == 1)
		p = s;

	counter++;	

	if (*s == '\0')
	{
		counter = 1;
		return s;
	}

	save = s[0];	
	reverse(s+1);	
	*p++ = save;	

	return s;
}

char * itoa(int n, char * s)
{	
	char * p = s;

	do
	{
		*p++ = n % 10 + '0';
		n = n / 10;		
	} while (n);

	*p = '\0';

	reverse(s);

	return s;
}
int myatox(char str[])
{
	int i, len, res = 0;
	len = strlen(str);
	for (i = 0; i < len; i++)
	{
		res *= 16;
		if ((str[i] >= 'a') && (str[i] <= 'f'))
			res += (str[i] - 'a' + 10);
		else
			res += (str[i]-'0');
	}
	return res;
}
