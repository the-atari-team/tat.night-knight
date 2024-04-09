; -*- text -*-
;DIV10-Function
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2022

 .local

?temp=@REG

; divide a given byte value (0-255) by 10
@div10
@div10_i
; and Byte
 LDY #1
 LDA (@HEAP_PTR),Y ; low Wert holen

; FOUND: https://forums.nesdev.com/viewtopic.php?f=2&t=11336
; Divide by 10
; 17 bytes, 30 cycles
  lsr
  sta  ?temp
  lsr
  adc  ?temp
  ror
  lsr
  lsr
  adc  ?temp
  ror
  adc  ?temp
  ror
  lsr
  lsr

  tay
  ldx #0
  rts
