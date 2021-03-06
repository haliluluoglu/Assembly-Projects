mydata 	SEGMENT PARA 'veri'
		dizi DW 0Dh,18h,1Fh,0fbh,28h,0Bh,01h,34h,14h,0FFh,1h,2h,3h,1Bh,0Ah,0Ah,0FFh,19h,42h,0FFh
		sonuc 	DW 20 DUP(0)
		boyut 	DW 0Ah
mydata 	ENDS


mystack	SEGMENT PARA STACK 'yigin'
		DW 30 DUP(?)
mystack	ENDS

mycode	SEGMENT	PARA 'kod'
		ASSUME DS:mydata,CS:mycode,SS:mystack
ANA 	PROC FAR
		PUSH DS
		XOR AX,AX
		PUSH AX
		MOV AX,mydata
		MOV DS,AX
		XOR BX,BX
		XOR DX,DX
		MOV CX,boyut
don:	XOR AX,AX
		MOV AL,dizi[BX]
		PUSH AX
		MOV AL,dizi[BX+10]
		PUSH AX
		CALL MULT
		
		SHL BX,1
		POP [BX+0014h]
		SHR BX,1
		ADD BX,1
		LOOP don
	    RETF
ANA 	ENDP

MULT	PROC NEAR
		PUSH BP
		PUSH BX
		PUSH DX
		MOV BP,SP
		MOV BX,[BP+8]
		MOV DX,[BP+10]
		
		CMP BX,1
		JNZ zip1
		MOV [BP+10],DX
		JMP zip3
		NOP
zip1:	TEST BX,0001h
		JZ zip2
		SHR BX,1
		PUSH BX
		MOV BX,DX
		SHL DX,1
		PUSH DX
		CALL MULT
		
		POP [BP+10]
		ADD [BP+10],BX
		JMP zip3
		NOP
zip2:	SHR BX,1
		SHL DX,1
		PUSH DX
		PUSH BX
		CALL MULT
		POP [BP+10]	
		
zip3:	POP DX
		POP BX
		POP BP
		RET 2
MULT	ENDP
mycode	ENDS
		END 	ANA