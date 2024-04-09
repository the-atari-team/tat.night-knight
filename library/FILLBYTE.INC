; -*- text -*-
;FILLBYTE-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;

    .LOCAL

; @clearbyte(start address, count of bytes)
; like @fillbyte(0, start address, count of bytes)
;.if .ref @clearbyte_ii
@clearbyte
@clearbyte_ii
 LDY #1
 LDA #0
 STA @REG
 BEQ ?inner_2_parameter

; jmp @fillbyte_iii
;.endif

; fill memory with a given byte
; @fillbyte(byte to fill, start address, count of bytes)
;.if .ref @fillbyte_iii
@fillbyte
@fillbyte_iii
; eigentliches Byte
 LDY #1
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG

; nach Adresse
 LDY #3
?inner_2_parameter
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+2
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+3

?length=@REG+4

; length
 INY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?length
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX             ; oberen Wert merken fuer Auswertung, ob nicht doch FILL255 genutzt werden kann
 STA ?length+1

 LDA ?length
 ORA ?length+1        ; length of 0, no fill at all!
 BEQ ?FILLEND

 CPX #0
 BEQ ?FILL_0_TO_255_LOOP

 LDY #0

 LDA @REG
?FILLLOOP_3
 STA (@REG+2),Y       ; use unroll for little speedup
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y       ; 8 * 8 + 3(bne) cycles for 8 bytes
 INY                  ; instead of 11 cycles per byte
 BNE ?FILLLOOP_3

; 11 * 256 == 2816
; 8*8+3 * 32 == 2144 -> 31% faster

 INC @REG+3

 DEX
 BNE ?FILLLOOP_3

 LDA ?length  ; last Bytes

?FILL_0_TO_255_LOOP
 CMP #0            ; nicht entfernen!
 BEQ ?FILLEND

 TAY
 AND #1
 BEQ ?FILL_EVEN

 LDA @REG
 DEY
 STA (@REG+2),Y
 BEQ ?FILLEND      ; bei length == 1 hier springen!


?FILL_EVEN
 LDA @REG

?FILLLOOP
 DEY               ; use unroll to speedup (2x)
 STA (@REG+2),Y
 DEY
 STA (@REG+2),Y
 BNE ?FILLLOOP

?FILLEND
 RTS
;.ENDIF
