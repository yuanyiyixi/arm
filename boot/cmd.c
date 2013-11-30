#include "my_printf.h"
#include "lib.h"
int cmp(const char *a, const char *b)
{
	while((*a && *a != '\n') || *b)
	{
		if(*a != *b)
			return 0;
		a++;
		b++;
	}
	return 1;
}
int loadb(int argc, char *argv[])
{
	myprintf("recive the file...");
	do_load_serial_bin(argc,argv);
	return 0;
}
int go(int argc, char *argv[])
{
	int n = 0;
	n = myatox(argv[1]+2);
	(*(void (*)(void))n)();
	return 0;
}
int md(int argc, char *argv[])
{
	int n, i, j;
	n = myatox(argv[1]+2);
	for (i = 0; i < 16; i++)
	{
		myprintf("%x: ", n);
		for (j = 0; j < 4; j++)
			myprintf("%x ", *(int *)(n + 4*j));
		for (j = 0; j < 16; j++)
		{
			if ((*(char *)(n + j) < 32) ||( *(char *)(n + j) > 126) )
			myprintf(".");
			else
			myprintf("%c", *(char *)(n + j));
		}
		n += 16;
			myprintf("\n");
	}
	return 0;
}
