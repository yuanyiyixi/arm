#define NFCONF	(*(volatile unsigned int *)0xB0E00000)
#define NFCONT	(*(volatile unsigned int *)0xB0E00004)
#define NFCMMD	(*(volatile unsigned int *)0xB0E00008)
#define NFADDR	(*(volatile unsigned int *)0xB0E0000C) 
#define NFDATA	(*(volatile unsigned int *)0xB0E00010)
#define NFSTAT	(*(volatile unsigned int *)0xB0E00028)

#define MP0_3CON	(*(volatile unsigned int *)0xE0200320)

#define PAGe_SIZE	2048

void nand_init(void)
{
	NFCONF |= 1<<12 | 1 << 8 | 1 <<4;

	NFCONF |= 1<<1;

	NFCONT |= 1<<0;

	NFCONT &= ~(1<<1);

	MP0_3CON = 0x22222222;

	NFCMMD = 0xff;

	while((NFSTAT & (1<<0)) == 0)
		;
		NFCONT |= (1<<1);

	return;
}
void nand_read_id(char id)
{
	int i;
	NFCMMD = 0x90;
	NFADDR = 0x00;
	for (i = 0; i < 5; i++)
		id[i] = NFDATA;
	return;
}
void nand_read_page(int addr, char buf[])
{
	int i;
	char tmp;
	NFCONT &= ~(1<<1); 

	NFCMMD = 0x00;

	NFADDR = (addr>>0) & 0xFF;
	NFADDR = (addr>>8) & 0x7;
	NFADDR = (addr>>11) & 0xFF;
	NFADDR = (addr>>19) & 0xFF;
	NFADDR = (addr>>27) & 0x1;

	NFCMMD = 0x30;

	while ((NFSTAT & (1<<0)) == 0)
}
