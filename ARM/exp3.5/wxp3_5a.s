	AREA EXAMPLE,CODE,READONLY
	ENTRY
	IMPORT b
START
	MOV SP,#0x300000 
	MOV R1,#0x11 
	MOV R2,#0x22 
	MOV R3,#0x33 
	MOV R4,#0x44 
	MOV R5,#0x55 
	STMFA R13!,{R2-R5}
	MOV R2,#0X77   
	LDMFA R13!,{R2-R5}  
	MOV SP,#0x400000 
	STMEA R13!,{R1-R5} ;���Ĵ���R1��R5���ݴ����ջ��EA����δ�ģ�
	MOV SP,#0x5400000 
	STMFD R13!,{R2-R5} ;���Ĵ���R2��R5���ݴ����ջ 
	
	MOV R3,#0X66 
	LDMFD R13!,{R2-R5} ;��FD��ģʽ�Ӷ�ջ�л�ԭ�Ĵ�����ֵ
	MOV SP,#0x600000 
	STMED R13!,{R2-R4} ;���Ĵ���R2��R4���ݴ����ջ

	BL b
	
	B .
	END
