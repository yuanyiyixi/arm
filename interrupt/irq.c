#define GPH2CON	*((volatile unsigned int *)0xe0200c40)
#define EXT_INT_2_CON	*((volatile unsigned int *)0xe0200e08)
#define EXT_INT_2_MASK	*((volatile unsigned int *)0xe0200f08)
#define EXT_INT_2_PEND	*((volatile unsigned int *)0xe0200f48)

#define VIC0INTSELECT	*((volatile unsigned int *)0xf200000c)
#define VIC0INTENABLE	*((volatile unsigned int *)0xf2000010)
#define VIC0ADDRESS	*((volatile unsigned int *)0xf2000f00)
#define VIC0VECTADDR16	*((volatile unsigned int *)0xf2000140)
extern void re(void);
void irq_init(void (*fun)(void))
{
	GPH2CON = 0xf;
	EXT_INT_2_CON = 0x2;
	EXT_INT_2_MASK &= 0x0;

	VIC0INTSELECT &= ~(1<<16);
	VIC0INTENABLE |= (1<<16);
	VIC0ADDRESS = 0x0;
	VIC0VECTADDR16 = (unsigned int)fun;

	re();	//中断核心层

	return;
}
void clear(void) 
{
	EXT_INT_2_PEND = 1<<0;
    VIC0ADDRESS = 0x0;
	return;
}
