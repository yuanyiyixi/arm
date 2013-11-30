	area sort,code,readonly
	code32
	
	export bubble
bubble
	mov r2,#0	;i =0
loop1
	add r2,r2,#1	;i = i+1
	cmp r2,r1
	movge pc,lr
	mov r3,#0	;j = 0
	
loop2
	
	sub r4,r1,r2	;r4 = n - i
	cmp r3,r4	;±È½Ï j < n - i
	
	bge loop1	;j >= n - i Ö´ÐÐ
	
	ldr r6, [r0,r3,lsl#2]	;a[j]
	add r3,r3,#1
	ldr r5, [r0,r3,lsl#2]  	;a[j+1]
	
	cmp r5,r6
	bge loop2				;a[j] <= a[j+1]
	
	str r6,[r0,r3,lsl#2]
	sub r3,r3,#1
	str r5,[r0,r3,lsl#2]
	
	add r3,r3,#1
	b loop2
	
	end

	