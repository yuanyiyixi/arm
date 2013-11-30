#include "uart.h"

typedef int * va_list;
#define va_start(ap, fmt) ap = (va_list)&fmt	//ap->&fmt
#define va_arg(ap, type) (type)(*++ap)			//ap,type,change
#define va_end(ap)		 ap = (void *)0			

void myputchar(char ch)
{
	if (ch == '\n')
		uart0_putchar('\r');
	uart0_putchar(ch);
	return ;
}
int myputs(const char *s)
{
	char *p = s;
	myputchar('8');

	while(*p)
	{
		myputchar(*p);
		p++;
	}
	myputchar('0');
	return (p - s);	//return the length of write
}
char * mygets(char *s)
{
	char ch;
	while((ch = uart0_getchar()) != '\r')
	{
		*s = ch;
		s++;
		uart0_putchar(ch);
	}
	*s++ = '\r';
	*s++ = '\n';
	*s = '\0';
	return s;
}
int strlen(const char *s)
{
	const char *p = s;
	while (*p)
		p++;
	return (p - s);
}
char * reverse(char *s)
{
	static int counter = 1;
	static char *p;
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
char *itoa(int n,char *s)
{
	char *p = s;
	while(n)	
	{
		*p++ = n%10 + '0';
		n = n/10;
	}

	*p = '\0';

	reverse(s);

	return s;
}
int myprintf(const char *format,...)
{
	char c;
	va_list ap;
	char c_val;
	int i_val;
	char * p_val;
	char buf[10];

	va_start(ap,format);	//ap is format's address
	while((c = *format) != '\0')
	{
		if (c == '%')
		{
			c = *++format;
			switch(c)
			{
				case 's':
					p_val = va_arg(ap, char *);
					myputs(p_val);
					break;
				case 'c':
					c_val = va_arg(ap, int);
					myputchar(c_val);
					break;
				case 'd':
					i_val = va_arg(ap, int);
					itoa(i_val, buf);
					myputs(buf);
					break;
				default:
					break;
			}
		}
		else 
			myputchar(c);
		format++;
	}
	va_end(ap);
	return 0;
}
