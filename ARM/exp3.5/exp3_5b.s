	AREA EXAMPLE,CODE,READONLY
	EXPORT b
b
	MOV R1,#0x01 
	MOV R2,#0x04 
	MOV R3,#0x03 
	MOV R4,#0x04 
	MOV R5,#0x05 
	LDR R0,=0x100000 ;�˴���LDR��һ��αָ�=�ſ��԰�0x100000ֱ�Ӹ�ֵ��R0 
	STMIA R0,{R1-R3}  ;��������ݿ�Ķ�Ĵ���Ѱַ
	LDMIA R0,{R6-R8} 
	LDR R0,=0x300000 
	STMIB R0,{R1-R3} ;��Ĵ���Ѱַ 
	LDR R0,=0x200008 
	STMDA R0,{R1-R3,R5}  
	STMDA R0!,{R1-R3,R5}   ;R0!��ʾ��ַд�أ�ִ����洢������R0�е�ֵ������
	LDR R0,=0x210000 
	
	MOV PC,LR
	
	END