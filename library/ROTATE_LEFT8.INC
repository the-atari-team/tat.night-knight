 .local

; rotate_left(value, bits)
; rotate a byte by n bits
@rotate_left8
@rotate_left8_ii
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen
      STA @REG

      LDY #3
      LDA (@HEAP_PTR),Y ; wert holen
      AND #$07          ; maxvalue ist 7
      TAX
      BEQ ?NO_ROTATE_LEFT8

      LDA @REG

?ROTATE_LEFT_LOOP
      ASL
      bcc ?no_carry

      ORA #$01
?no_carry
      DEX
      BNE ?ROTATE_LEFT_LOOP

      TAY
      RTS

?NO_ROTATE_LEFT8
      LDY @REG
      RTS
