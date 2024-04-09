; -*- text -*-
;STRING-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;
     .LOCAL

; Ermittle die Laenge eines Strings
; Wir supporten keine Strings laenger als 254 bytes!

;.if .ref @strlen_i
@STRLEN
@STRLEN_I
     jsr @heap_parameter_1_to_reg

     LDY #0
?STRLEN_LOOP
     LDA (@REG),Y
     CMP #255
     BEQ ?STRLEN_END

     INY
     JMP ?STRLEN_LOOP

?STRLEN_END
     LDX #0
     RTS
;.endif

; small Helper function to copy the first parameter to @REG
@heap_parameter_1_to_reg
     LDY #1
     LDA (@HEAP_PTR),Y
     STA @REG
     INY
     LDA (@HEAP_PTR),Y
     STA @REG+1
     RTS

; small Helper function to copy the second parameter to @REG+2
@heap_parameter_2_to_reg_plus_2
     LDY #3
     LDA (@HEAP_PTR),Y
     STA @REG+2
     INY
     LDA (@HEAP_PTR),Y
     STA @REG+3
     RTS

; @instr(adr:string, byte)
; liefert die position an der byte innerhalb von string vorkommt
; @return -1 wenn nichts gefunden, sonst position [0, strlen-1]
;.if .ref @instr_ii
@instr
@instr_ii
     jsr @heap_parameter_1_to_reg

     jsr @heap_parameter_2_to_reg_plus_2

      LDY #0
?IN_LOOP
      LDA (@REG),Y
      CMP #255
      BEQ ?IN_END_FAIL   ; --> $FF gefunden im Suchstring, wir sind fertig

      cmp @reg+2
      beq ?IN_END_FOUND

      INY
      BNE ?IN_LOOP

; hier: wir haben alle 256 moeglichen Werte kontrolliert und nichts gefunden

?IN_END_FAIL
      ldy #255
      ldx #255
      rts

?IN_END_FOUND      ; Y-Reg enthaelt Position
      ldx #0
      rts
;.endif

;// TODO:
;// add str_insert_at(adr:stringto, adr:stringfrom, n)
;// insert a given from-string at position n in to-string, this will move forward n bytes
;// if string will be too long, all over 255 will cut
;// insert("WORLD", "HALLO ", 0) -> "HALLO WORLD"
;// insert("HALLO WORLD", " NEW", 5) -> "HALLO NEW WORLD"
;// the new length is strlen(stringto) + strlen(stringfrom) but not longer then 255
;//
;// add str_replace_at(adr:stringto, adr:stringfrom, n, m)
;// replace in to-string at position n, count of m bytes by from-string
;// replace("NEW WORLD","HALLO", 0, 3) -> "HAL WORLD"
;// The new String will not be longer
;//
;// add str_append(adr:stringto, adr:stringfrom)
;// addend a given from-string at the end of to-string, result is max 255 char long
;// append("HALLO ", "WORLD") -> "HALLO WORLD"
;// the new length is strlen(stringto) + strlen(stringfrom) but not longer then 255
