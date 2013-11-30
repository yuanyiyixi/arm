	AREA EXAMPLE,CODE,READONLY
	EXPORT b
b
	MOV R1,#0x01 
	MOV R2,#0x04 
	MOV R3,#0x03 
	MOV R4,#0x04 
	MOV R5,#0x05 
	LDR R0,=0x100000 ;此处的LDR是一条伪指令，=号可以把0x100000直接赋值给R0 
	STMIA R0,{R1-R3}  ;针对于数据块的多寄存器寻址
	LDMIA R0,{R6-R8} 
	LDR R0,=0x300000 
	STMIB R0,{R1-R3} ;多寄存器寻址 
	LDR R0,=0x200008 
	STMDA R0,{R1-R3,R5}  
	STMDA R0!,{R1-R3,R5}   ;R0!表示地址写回，执行完存储操作后R0中的值被更新
	LDR R0,=0x210000 
	
	MOV PC,LR
	
	END