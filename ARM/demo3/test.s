	area example,code,readonly
	code32
	
	export strcopy
strcopy
	ldrb r2,[r1],#1
	strb r2,[r0],#1
	
	cmp r2,#0
	bne strcopy
	
	mov pc,lr
	
	end