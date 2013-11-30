#define GPD0CON	*((volatile unsigned int *)0xe02000a0)
#define TCFG0	*((volatile unsigned int *)0xe2500000)
#define TCFG1	*((volatile unsigned int *)0xe2500004)
#define TCON	*((volatile unsigned int *)0xe2500008)
#define TCNTB0	*((volatile unsigned int *)0xe250000c)
#define TCMPB0	*((volatile unsigned int *)0xe2500010)
#define TCNTO0	*((volatile unsigned int *)0xe2500014)
#define TINT_CSTAT	*((volatile unsigned int *)0xe2500044)

#define VIC0INTSELECT	*((volatile unsigned int *)0xf200000c)
#define VIC0INTENABLE	*((volatile unsigned int *)0xf2000010)
#define VIC0RAWINTR	*((volatile unsigned int *)0xf2000008)
#define VIC0ADDRESS	*((volatile unsigned int *)0xf2000f00)
#define VIC0VECTADDR21	*((volatile unsigned int *)0xf2000154)
void irq_init(void (*fun)(void))
{
//	GPD0CON = 0xf;
	TCFG0 = 65;
	TCFG1 = 0x4;
	TCNTB0 = 62500;

	TCON = 1<<1;
	TCON &= ~(1<<1);
	TCON |= 1<<0;
	TCON |= 1<<3;

	TINT_CSTAT |= 1<<0;

	VIC0INTSELECT &= ~(1<<21);
	VIC0INTENABLE |= (1<<21);
	VIC0ADDRESS = 0x0;
	VIC0VECTADDR21 = (unsigned int)fun;

	re();	//中断核心层

	return;
}
void clear(void) 
{
	TINT_CSTAT |= 1<<5;
    VIC0ADDRESS = 0x0;
	return;
}
