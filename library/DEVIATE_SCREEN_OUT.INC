;DEVIATE_SCREEN_OUTPUT-Library
;-*- text -*-
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2022
;

; @DEVIATE_SCREEN_OUT wird fuer jedes Zeichen
; ausgefuehrt, wenn @printfd(...) verwendet wird

 .local

@DEVIATE_SCREEN_OUT
  pha

  ldy #1
  lda ?waitstate
  sta (@HEAP_PTR),Y
  iny
  lda #0
  sta (@heap_ptr),y
  jsr @sleep_i

  pla
  jmp @FASTSCREEN_OUT

; we can set the sleep time
@DEVIATE_SET_SLEEP_AT_PRINTFD
@DEVIATE_SET_SLEEP_AT_PRINTFD_I
 ldy #1
 lda (@heap_ptr),y

 sta ?waitstate
 rts

; we can set the sleep time, no sleep time
; this is also the default at startup
@DEVIATE_NO_SLEEP_AT_PRINTFD
  lda #0
  sta ?waitstate
  rts

?waitstate
 .byte 0
