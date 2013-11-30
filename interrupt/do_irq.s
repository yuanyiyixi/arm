.globl do_irq
do_irq:
	stmfd r13!,{r0-r12,r14} 
	bl clear
	bl func

	ldmfd r13!,{r0-r12,r15}^
