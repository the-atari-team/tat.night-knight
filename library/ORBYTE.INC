; -*- text -*-
;BASIC-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;

    .LOCAL

?AND_MEMONIC=$29
?ORA_MEMONIC=$09
?XOR_MEMONIC=$49

; @xorbyte(Value, adresse, length)
; dabei wird vorwaerts gelaufen
; Laden einer Adresse, Value per XOR filtern und an selbe Adresse wieder speichern.
; arbeitet nur mit Byte length!
@xorbyte
@xorbyte_iii
 lda #?XOR_MEMONIC ; eor #0
 sta ?orvalue
 jmp ?orbyte_start

; @andbyte(Value, adresse, length)
; dabei wird vorwaerts gelaufen
; Laden einer Adresse, Value per AND filtern und an selbe Adresse wieder speichern.
; arbeitet nur mit Byte length!
@andbyte
@andbyte_iii
 lda #?AND_MEMONIC ; and #0
 sta ?orvalue
 jmp ?orbyte_start

; orbyte Value, adresse, length
; dabei wird vorwaerts gelaufen
; Laden einer Adresse, Value per ORA filtern und an selbe Adresse wieder speichern.
; arbeitet nur mit Byte length!
@orbyte
@orbyte_iii
 lda #?ORA_MEMONIC ; ora #0
 sta ?orvalue

?orbyte_start
 LDY #1
 LDA (@HEAP_PTR),Y ; value for or, and, xor
 STA ?orvalue+1

; Adresse
 LDY #3
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+2
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+3

; length
; LDY #5
 INY
 LDA (@HEAP_PTR),Y ; low Wert holen
 TAX

 LDY #0

?ORLOOP            ; LOOP for upper 256 Bytes
 LDA (@REG+2),Y
?orvalue
 ORA #0            ; hier wird der Wert manipuliert (and, or, xor)
 STA (@REG+2),Y
 INY
 DEX
 BNE ?ORLOOP

 RTS
