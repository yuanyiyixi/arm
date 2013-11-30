typedef int * va_list;
#define va_start(ap, fmt) ap = (va_list)&fmt	//ap->&fmt
#define va_arg(ap, type) (type)(*++ap)			//ap,type,change
#define va_end(ap)		 ap = (void *)0			

void myputchar(char ch)
{
	if (ch == '\n')
		ch = '\0';
	uart0_putchar(ch);
	return ;
}
int myputs(const char *s)
{
	const char *p = s;
	while(*p)
	{
		myputchar(*p);
		p++;
	}
	return (p - s);	//return the length of write
}
char * mygets(char *s)
{
	char ch;
	while((ch = uart0_getchar()) != '\r')
	{
		*s = ch;
		s++;
	}
	*s++ = '\r';
	*s++ = '\n';
	*s = '\0';
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
					//myputchar(i_val);
					break;
			}
		}
		else 
			myputchar(c);

	}
	va_end(ap);
	return 0;
}
