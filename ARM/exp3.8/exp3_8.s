	area example,code,readonly
	entry
start ldr r1,=srcstr
	ldr r0,=dststr
	
	bl strcopy
	mov r0,#3
	
	b .
strcopy
	ldrb r2,[r1],#1
	strb r2,[r0],#1
	cmp r2,#0
	bne strcopy
	mov pc,lr
	
	area strings,data,readwrite
srcstr dcb "First string - source",0
dststr dcb "Second string - destination",0
	end