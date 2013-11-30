int help(int argc, char *argv[]);
int loadb(int argc, char *argv[]);
int go(int argc, char *argv[]);
int md(int argc, char *argv[]);

struct cmd
{
	char name[16];
	int (*pf)(int argc, char *argv[]);
}cmds[]=
{
	"help",help,
	"loadb",loadb,
	"go",go,
	"md",md
};
