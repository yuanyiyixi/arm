	area example,code,readonly
	entry
start
	mov r1,#0x04
	mov r2,#0x04
	subs r3,r2,r1
	
	mov r5,#0x300
	add r7,r5,r2,lsl#0x4
	cmp r5,r7
	
	subs r1,r1,#0x01
	subs r1,r1,#0x03
	moveq r2,#0x0
	
	b start
	end