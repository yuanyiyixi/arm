#include "nand.h"

void copy_myself()
{
	nand_init();
	nand_read(0x0, (char *)0x20000000,0x8000);
}
