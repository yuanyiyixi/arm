	area example,code,readonly
	entry
start mov r1,#0x04
	mov r2,r1
	mov r3,r2,lsl#4
	
	ldr r3,[r2]
	mov r0,pc
	mov r3,#0x10
	ldr r4,[r3,#0x0c]
	
	ldmia r1!,{r4-r7,r12}
	
	mov sp,#0x30
	
	mov r2,#0x22
	mov r3,#0x33
	mov r4,#0x44
	mov r5,#0x55
	stmfa r13!,{r2-r5}
	
	ldmfa sp!,{r2-r5}
loop bl add_sub
	b loop
	
add_sub
	adds r0,r0,r1
	mov pc,lr
	
	end