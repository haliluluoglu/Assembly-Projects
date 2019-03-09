mystack SEGMENT PARA STACK 'stack'
		DW 	32 	DUP(?)
mystack	ENDS
mydata 	SEGMENT	PARA 'data'
		CR 		EQU 13
		LF		EQU 10
		Eleman  EQU 100    
		boyut 	DB	?
		dizi 	DB ?
		
		MSG1	DB  'boyut: ', 0
		MSG2 	DB 	CR,LF, 'eleman: ', 0 
		HATA    DB  CR,LF, 'Dikkat sayi vermediniz.Yeniden giris yapiniz.', 0
		HATA1	DB	CR,LF, 'Dizinin boyutu en fazla 100 olabilir!', 0
		HATA2 	DB  CR,LF, 'Verilebilecek rakam sayisini astiniz!', 0
		HATA3	DB	CR,LF, '-128 den kucukk bir sayi giremezsiniz!', 0
		HATA4	DB 	CR,LF, '+127 den buyuk bir sayi giremezsiniz!', 0
		SONUC	DB	CR,LF, 'Dizinin siralanmis hali: '
mydata 	ENDS
mycode 	SEGMENT	PARA 'code'
		ASSUME CS:mycode, DS:mydata, SS:mystack
ANA 	PROC FAR
		PUSH DS
		XOR AX, AX
		PUSH AX
		MOV AX, mydata
		MOV DS, AX
		
boyutal:MOV AX, OFFSET MSG1       
		CALL PUT_STR
		CALL GETN
		;CMP AX, 100
		;JA	hataM1
		MOV boyut, AL
		
		;taking elements of array from user
		
		MOV CX, WORD PTR boyut

       	MOV AX, OFFSET MSG2
		CALL PUT_STR
		XOR SI, SI
   don:	CALL GETN
		;CMP AX, 127
		;JA 	hataM3
		;CMP AX, -128
		;JL hataM2
		MOV dizi[SI], Al
		INC SI   
		LOOP don
		;CALLING QUIKSORT
		;XOR CL, CL
		;MOV CH, boyut
		;DEC CH
		;CALL QUIKSORT
		
		
		
	
;hataM1:	MOV AX, OFFSET MSG1
;		CALL PUT_STR
	;	JMP boyutal
;hataM2:	MOV AX, OFFSET HATA2
	;	CALL PUT_STR
		;JMP input
;hataM3:	MOV AX, OFFSET HATA3
	;	CALL PUT_STR
		;JMP input    
		           
		
		RETF
ANA		ENDP 

GETN    PROC NEAR
        PUSH BX
        PUSH CX
        PUSH DX
GETN_START:
        MOV DX, 1
        XOR BX, BX
        XOR CX, CX
NEW:
        CALL GETC
        CMP AL, CR
        JE FIN_READ
        CMP AL, '-'
        JNE CTRL_NUM
NEGATIVE:
        MOV DX, -1
        JMP NEW
CTRL_NUM:
        CMP AL, '0'
        JB error
        CMP AL, '9'
        JA error
        SUB AL, '0'        
        MOV BL, AL
        MOV AX, 10
        PUSH DX
        MUL CX
        POP DX
        MOV CX, AX
        ADD CX, BX
        JMP NEW
ERROR:  
        MOV AX, OFFSET HATA
        CALL PUT_STR
        JMP GETN_START
FIN_READ:
        MOV AX, CX
        CMP DX, 1
        JE FIN_GETN
        NEG AX
FIN_GETN:
        POP DX
        POP CX
        POP DX
        RET
GETN    ENDP    

PUTN    PROC NEAR
        PUSH CX
        PUSH DX
        XOR DX, DX
        PUSH DX
        MOV CX, 10
        CMP AX, 0
        JGE CALC_DIGITS
        NEG AX
        PUSH AX
        MOV AL, '-'
        CALL PUTC
        POP AX
CALC_DIGITS:
        DIV CX
        ADD DX, '0'
        PUSH DX
        XOR DX, DX
        CMP AX, 0
        JNE CALC_DIGITS
DISP_LOOP:
        POP AX
        CMP AX, 0
        JE END_DISP_LOOP
        CALL PUTC
        JMP DISP_LOOP
END_DISP_LOOP:
        POP DX
        POP CX
        RET
PUTN    ENDP

PUTC    PROC NEAR
        PUSH AX
        PUSH DX
        MOV DL, AL
        MOV AH, 2
        INT 21H
        POP DX
        POP AX
        RET
PUTC    ENDP

GETC    PROC NEAR
        MOV AH, 1h
        INT 21H
        RET
GETC    ENDP
   

PUT_STR PROC NEAR
		PUSH BX
		MOV BX, AX
		MOV AL, BYTE PTR [BX]
	PUT_LOOP:
		CMP AL, 0
		JE PUT_FIN
		CALL PUTC
		INC BX
		MOV AL, BYTE PTR [BX]
		JMP PUT_LOOP
	PUT_FIN:
		POP BX
		RET
PUT_STR	ENDP   

QUIKSORT PROC NEAR
		PUSH CX
dongu1:	CMP CL, CH
		JAE	Son
		MOV	BL, CL
		MOV AL, CL
		MOV AH, CH
while1:	CMP AL, AH
		JGE while1son
while2: MOV DL, dizi[DI]
		CMP DL, dizi[SI]
		JG while3
		INC AL
while3:	MOV DL, dizi[DI]
		CMP AL, dizi[SI]
		JLE dongu2
		DEC AH
dongu2:	CMP AL, AH
		JAE while1son
		CALL SWAP
		JMP while1

while1son: PUSH BX
		MOV BL, AL
		CALL SWAP
		POP BX
		
		;FIRST RECURSIVE QUIKSORT
		DEC AH
		MOV CH, AH
		POP CX
		CALL QUIKSORT
		;SECOND RECURSIVE QUIKSORT
		INC AH
		MOV CL, AH
		;POP CH
		CALL QUIKSORT
Son:	RET
QUIKSORT ENDP   

SWAP	PROC NEAR
		MOV DL, AL
		XCHG DL, dizi[SI]
		RET
SWAP	ENDP

mycode 	ENDS
		END ANA