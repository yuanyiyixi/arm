.globl _start
_start:
	ldr sp,=0xD0037000

	ldr r0,=0xE2700000
	mov r1,#0
	str r1,[r0]

	mrs r0,CPSR
	bic r0,r0,#0xC0
	msr CPSR,r0

	bl clock_init

	bl mem_ctrl_asm_init

	b c_entry
