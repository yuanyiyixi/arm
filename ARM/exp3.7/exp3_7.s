	area example,code,readonly
	entry
start
	mov r0,#0x31
	mov r2,#0x50
tag1
	mov r3,#0x100
	tst r0,#0x01
	moveq r2,#0x3000
	tst r1,#0x0f
	strne r0,[r2,#2]
	cmp r0,#0x0
	addne r0,r2,r3,lsl #1
tag2
	cmp r2,r3
	andeq r2,r2,#0x3
	cmp r3,#0x100
	bne tag1
	tst r0,#0x01
	beq tag2
	
	b start
	end