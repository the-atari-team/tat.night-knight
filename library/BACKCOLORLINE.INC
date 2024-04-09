; -*- text -*-
;BASIC-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;

  .LOCAL

; @backcolorline(color) setzt die Hintergrundfarbe auf color in exakt der Bildschirmzeile
; in der sich der Elektronenstrahl gerade befindet.
;.IF .REF @backcolorline_i
@backcolorline
@backcolorline_i
 LDY #1
 LDA (@HEAP_PTR),Y

 STA WSYNC

 LDX 712 ; COLOR0+4
 STA COLBK
 STA WSYNC

 STX COLBK
 RTS
;.ENDIF
