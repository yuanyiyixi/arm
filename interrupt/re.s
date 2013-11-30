.globl re 
re:
		MRS R0,CPSR
		BIC R0,R0,#0x80
		MSR CPSR,R0

		MOV PC,LR
