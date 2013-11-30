#include "gpio.h"
//#include "my_stdio.h"
//#include "my_printf.h"
#include "nand.h"



//in my_shell.c
extern int help(int argc, char *argv[]);


int beep_test(int argc, char *argv[])
{
	int i;
	beep_init();
	for (i = 0; i < 4; i++) {
		beep_on();
		delay(1);
		beep_off();
		delay(1);
	} 
	return 0;
}

typedef unsigned int __u32;
typedef unsigned char __u8;
typedef unsigned short __u16;

struct tag_header {
	__u32 size;
	__u32 tag;
};
struct tag_core {
	__u32 flags;		/* bit 0 = read-only */
	__u32 pagesize;
	__u32 rootdev;
};
struct tag_mem32 {
	__u32	size;
	__u32	start;	/* physical start address */
};

struct tag_initrd {
	__u32 start;	/* physical start address */
	__u32 size;	/* size of compressed ramdisk image in bytes */
};

struct tag_cmdline {
	char	cmdline[1];	/* this is the minimum size */
};

struct tag {
	struct tag_header hdr;
	union {
		struct tag_core		core;
		struct tag_mem32	mem;
		struct tag_initrd	initrd;
		struct tag_cmdline	cmdline;
	} u;
};

#define tag_next(t)	((struct tag *)((__u32 *)(t) + (t)->hdr.size))
#define tag_size(type)	((sizeof(struct tag_header) + sizeof(struct type)) >> 2)

/* The list must start with an ATAG_CORE node */
#define ATAG_CORE	0x54410001
/* it is allowed to have multiple ATAG_MEM nodes */
#define ATAG_MEM	0x54410002
/* describes where the compressed ramdisk image lives (physical address) */
#define ATAG_INITRD2	0x54420005
/* The list ends with an ATAG_NONE node. */
#define ATAG_NONE	0x00000000
/* command line: \0 terminated string */
#define ATAG_CMDLINE	0x54410009

const char cmd[] = "root=/dev/mtdblock4 console=ttySAC0,115200 init=/linuxrc lcd=H43";

void init_taglist(int addr)
{
	struct tag * p;
	int i;
	
	p = (struct tag*) addr;
	p->hdr.tag  =  ATAG_CORE;
	p->hdr.size = tag_size(tag_core);
	p->u.core.flags = 1;
	p->u.core.pagesize = 4096;
	p->u.core.rootdev = 0x00000000;

	p = tag_next(p);
	p->hdr.tag = ATAG_CMDLINE;
	p->hdr.size =  (sizeof (cmd) + sizeof(struct tag_header) + 3) >>2;	
	for(i=0; i< sizeof (cmd); i++)	
		p->u.cmdline.cmdline[i] = cmd[i];

	p = tag_next(p);
	p->hdr.tag = ATAG_MEM;
	p->hdr.size = tag_size(tag_mem32);
	p->u.mem.size = 256*1024*1024;
	p->u.mem.start = 0x20000000;

	p = tag_next(p);
	p->hdr.tag = ATAG_NONE;
	p->hdr.size = 0;
}

#define LINUX_BOOT_ADDR		0x20008000
//int bootm(int argc, char * argv[])
int bootm(void)
{
	int addr = LINUX_BOOT_ADDR;
	void (*fp)(int, int, int);
	int taglist_mem_address = 0x20000100;
	
	myprintf("loading linux from NandFlash 4M to SDRAM 0x%x...\n", LINUX_BOOT_ADDR);

	// copy kernel from flash 4M to sdram 0x20008000 with size of 8M
	nand_init();
	nand_read(0x400000, (char *)LINUX_BOOT_ADDR, 0x800000);
	fp = (void (*)(int, int, int))addr;
	
	init_taglist(taglist_mem_address);

	myprintf("lumit boot linux now...\n");
	fp(0, 3466, taglist_mem_address);
	
	return 0;
}

