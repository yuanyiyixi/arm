	area example,code,readonly
	entry
start
	mov r0,#0x02
	and r0,r0,#0x01
	mov r1,#0x0f7
	mov r3,#0x05
	and r2,r1,r3
	mov r0,#0x0c1
	orr r0,r0,#0x0f
	eor r2,r1,r0
	eor r2,r1,r0
	bic r1,r1,#0x0f
	bic r1,r2,r3
	
	b start
	end
	
	