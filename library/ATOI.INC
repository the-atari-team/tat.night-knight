; ascii to integer atoi(x)

 .local

@NEGATIVE_MARK=@REG+3

; convert ASCII Value to integer
; (x*256+y) = @atoi(adr:string)
;.if .ref @atoi_i
@ATOI
@ATOI_I
  LDY #1
  LDA (@HEAP_PTR),Y
  STA @OP
  INY
  LDA (@HEAP_PTR),Y
  STA @OP+1                ; address of given string

	LDY #0
	STY @REG
	STY @REG+1
  STY @NEGATIVE_MARK

  LDA (@OP),Y ; check if '-' exist and set negativ mark
  CMP #'-
  BNE ?DEC1

  LDA #1
  STA @NEGATIVE_MARK
  INY

?DEC1
	LDA (@OP),Y
	CMP #'0
	BCC ?NOZAHL
	CMP #'9+1
	BCS ?NOZAHL
	AND #$0F

	LDX #17
	BNE ?DEC3

?DEC2
	BCC ?DEC4 ;*+4
	ADC #10-1
?DEC4
	LSR
?DEC3
	ROR @REG+1
	ROR @REG
	DEX
	BNE ?DEC2

	INY
	BNE ?DEC1

?NOZAHL
  LDA @NEGATIVE_MARK
  BEQ ?NOT_NEGATIVE

; copied the NEG here, cost 12 bytes instead of 3 for jump, but no need to insert MATH.INC extra
; 16 bit Binary Negation
;@NEG_INNER
       SEC             ;Ensure carry is set
       LDA #0          ;Load constant zero
       SBC @REG+0      ;... subtract the least significant byte
       TAY             ;... and store the result
       LDA #0          ;Load constant zero again
       SBC @REG+1      ;... subtract the most significant byte
       TAX             ;... and store the result
       RTS

;  JMP @NEG_INNER    ; make @reg negitive and return (x*256+y)

?NOT_NEGATIVE
	LDY @REG
	LDX @REG+1
	RTS
;.endif
