; -*- text -*-
;RANDOM_MOD-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 2022
;

 .local

?mod=@REG
;
; @randomMod(x) returns a random value in Range [0-x) where x<255
; x=0 returns 0

; RAMDOM mod i
@randomMod
@randomMod_i
  ldy #1
  lda (@heap_ptr),y
  beq ?fail
  sta ?mod

  ldx #2
;  cmp #4
;  bcc ?less
;  inx
;  cmp #8
;  bcc ?less
;  inx
  cmp #16
  bcc ?less
  inx
  cmp #32
  bcc ?less
  inx
  cmp #64
  bcc ?less
  inx
;  cmp #128
;  bcc ?less

; modulus, returns in register A
?less
   lda RANDOM
   and ?filter,x
   sec
?modulus
   sbc @reg
   bcs ?modulus
   adc @reg
   tay

  ldx #0
  rts

?fail
  TAY
  LDX #0
  RTS

?filter
 .byte $07,$0F,$1F,$3F,$7F,$FF
