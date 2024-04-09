; -*- text -*-
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2022
;
; string alignment
; spaces in front of string
; spaces after string
; center a string

 .local

; @REG..@REG+3 wird von @atoi(n) verwendet
?align_string=@REG+4  ; 2
?string=@REG+6         ; 2
?align_length=@REG+8  ; 1
?align_length_half=@REG+9 ; 1

?stackpointer=@REG+10

; normalerweise koennen Strings bis zu 255 Zeichen lang werden
; da das Alignment aber wohl eher fuer Screen Ausgaben verwendet wird
; beschneiden wir die Laenge auf 130 Zeichen, sollte es nicht ausreichen
; muss dieser Source angepasst werden. So sparen wir 128 Bytes kostbaren Speicher.

?buffer=CASBUF

; aligniert einen String
; zentriert ^n
; linksbuendig <n
; rechtsbuendig >n
; n ist eine Zahl < buffergroesse
;
; @stralign(alignstring, string)

@stralign
@stralign_ii
 ldy #1
 lda (@heap_ptr),y
 sta ?align_string
 iny
 lda (@heap_ptr),y
 sta ?align_string+1      ; align string

 ldy #3
 lda (@heap_ptr),y
 sta ?string
 iny
 lda (@heap_ptr),y
 sta ?string+1             ; string to align

 tsx
 stx ?stackpointer

 ldy #0
 lda (?align_string),y    ; ^ < > sind erlaubt!
 iny
 cmp #'^
 beq ?center_string

 cmp #'<
 beq ?to_the_left

 cmp #'>
 beq ?to_the_right

 ldy #<?wrong_align_char
 ldx #>?wrong_align_char
 rts

; inner function to center a string
?center_string
 jsr ?prepare_to_the_left_right

 jsr ?strlen_string   ; String length in Y

 cpy #0
 beq ?to_the_left_loop_exit

 cpy ?align_length
 bcs ?just_return_string  ; align length too small!

 lda ?align_length
 lsr
 tax
 bcc ?no_correct
 inx
?no_correct
 stx ?align_length_half

 jsr ?strlen_string       ; String length in Y
 tya
 lsr                      ; String length half + align length half
 clc
 adc ?align_length_half
 tax                      ; Endposition in X
 dex
 dey
 jmp ?to_the_right_loop

; -------------------------------------------------------------------
; inner function to copy to the left
?to_the_left
 jsr ?prepare_to_the_left_right

 jsr ?strlen_string   ; String length in Y

 cpy #0
 beq ?to_the_left_loop_exit

 cpy ?align_length
 bcs ?just_return_string  ; align length too small!


 ldy #0
?to_the_left_loop
 lda (?string),y

 cmp #255
 beq ?to_the_left_loop_exit  ; end-mark do not copy within

 sta ?buffer,y
 iny
 bne ?to_the_left_loop

?to_the_left_loop_exit
 ldy #<?buffer
 ldx #>?buffer
 rts

; -------------------------------------------------------------------
; inner function to copy to the left
?to_the_right
 jsr ?prepare_to_the_left_right

 jsr ?strlen_string   ; String length in Y

 cpy #0
 beq ?to_the_left_loop_exit

 cpy ?align_length
 bcs ?just_return_string  ; align length too small!

 dey                  ; we stay at last char in ?string
 ldx ?align_length   ; stay on last position (on 255 end-mark)
 dex

?to_the_right_loop
 lda (?string),y
 sta ?buffer,x
 dex
 dey
 bpl ?to_the_right_loop

 ldy #<?buffer
 ldx #>?buffer
 rts

?align_length_value_too_big
 ldx ?stackpointer
 txs

 ldy #<?number_too_big
 ldx #>?number_too_big
 rts

; is the align number too low, return the string
?just_return_string
 ldy ?string
 ldx ?string+1
 rts


?prepare_to_the_left_right
 jsr ?get_number_from_align_string
 sty ?align_length
 cpy #127
 bcs ?align_length_value_too_big

; in Y-register should exist the end-mark
?fill_with_space
 lda #255
 sta ?buffer,y
 dey
 lda #32           ; copy space into buffer
?fill_with_space_loop
 sta ?buffer,y
 dey
 bpl ?fill_with_space_loop

 rts

; liefert zahl in y
?get_number_from_align_string
 ldx #0
?get_number_loop
 lda (?align_string),y     ; read char as its end
 sta ?buffer,x

 cmp #255
 beq ?get_number_exit_loop

 inx
 iny
 bne ?get_number_loop

?get_number_exit_loop
 ldy #1
 lda #<?buffer
 sta (@heap_ptr),y
 iny
 lda #>?buffer
 sta (@heap_ptr),y
 jmp @ATOI_I

; liefert in y
?strlen_string
 ldy #0

?strlen_loop
 lda (?string),y
 cmp #255           ; End-mark of string
 beq ?strlen_exit   ; --> end-mark arrived
 iny
 bne ?strlen_loop   ; TODO: Compiler must not support strings > 254 chars (255. char must be end-mark)

?strlen_exit
 rts                ; Y-Reg enthaelt die Laenge des Strings


?wrong_align_char
 .byte "WRONG FORMAT CHAR",255

?number_too_big
 .byte "FORMAT NUMBER TO BIG",255

; 128 bytes fuer den Buffer
;?buffer
; .ds 128
