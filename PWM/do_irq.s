.globl do_irq
do_irq:
	sub r14,r14,#4
	stmfd r13!,{r0-r12,r14} 

	bl clear
	bl func

	ldmfd r13!,{r0-r12,r15}^
.globl re 
re:
		MRS R0,CPSR
		BIC R0,R0,#0x80
		MSR CPSR,R0

		MOV PC,LR
