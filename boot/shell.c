#include "cmd.h"
#define NULL (void *)0

void parse(char *buf, int *argc, char *argv[])
{
	char *p = buf;
	*argc = 0;
	int flag = 0;

	while(*p)
	{
		if(flag == 0 && (*p != ' ' && *p != '\r'))
		{
			argv[*argc] = p;
			(*argc)++;
			flag = 1;
		}
		else 
			if(flag == 1 && (*p == ' ' || *p == '\r'))
			{
				*p = '\0';
				flag = 0;
			}
			p++;
	}
	argv[*argc] = NULL;
	return;
}
int help(int argc, char *argv[])
{
	int i;
		for (i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++)
				myprintf("--%s\n",cmds[i].name);
	return 0;
}
void myshell(void)
{
	char s[128];
	char *argv[8];
	int argc = 0, i;
	while(1)
	{
		myprintf("shell$ ");
		mygets(s);
		parse(s, &argc, argv);
		myputs("\n");
		for (i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i++)
			if(cmp(argv[0],cmds[i].name))
			{
				cmds[i].pf(argc,argv);
			}
	}
	return ;
}
