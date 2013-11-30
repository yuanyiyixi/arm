	area example,code,readonly
	entry
start
	mov r1,#0x10000
	mov r4,#0x20000
	mov r2,#0xf0000004
	mov r3,#0x1200
	mov r0,#0x1
	
	str r0,[r1]
	ldr r5,[r1]
	add r5,r1,#4
	mov r5,#0x7
	ldr r0,[r1,#4]
	ldr r0,[r1,#-4]
	ldr r0,[r1,#4]!
	ldr r0,[r1],#4
	ldr r0,[r1,r2]
	
	str r2,[r4]
	swp r0,r1,[r4]
	swp r0,r0,[r1]
	swpb r0,r1,[r2]
	swpb r0,r0,[r1]
	
	b start
	end