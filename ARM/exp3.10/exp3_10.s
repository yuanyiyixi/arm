	area example,code,readonly
	entry
start
	mov r1,#0x1
	mov r2,#0x2
	subs r1,r1,r2
	
	mrs r0,cpsr
	bic r0,r0,#0x1f
	orr r0,r0,#0x1f
	msr cpsr_cxsf,r0
	b .
	end