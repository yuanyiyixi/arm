	area example,code,readonly
	code32
	entry

	import g
	import glovbl
start mov r0,#1
	mov r1,#2
	mov r2,#3
	ldr r7,=glovbl
	ldr r3,[r7]
	bl g
	mov r8,r0
	b start
	end	
