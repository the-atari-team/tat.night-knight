; -*- text -*-
;MATH-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 2019
;
   .LOCAL

; HINT: Genau drauf achten, das immer x das hoeherwertige Byte nimmt

; SGN vorzeichen x * 256 + y := SGN(@REG1)
;.if .ref @sgn_i
@SGN
@SGN_I
      LDY #2
      LDA (@HEAP_PTR),Y ; get high value
      BMI ?SGNNEGATIV

      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y ; get low value

      ORA @REG+1
      BEQ ?SGNZERO

      LDY #1    ;positiv
      LDX #0
      RTS

?SGNNEGATIV
      LDY #255  ;negativ
      LDX #255
      RTS

?SGNZERO
      LDY #0    ;zero
      LDX #0
      RTS
;.endif

; Vorzeichen entfernen, immer positiv
;.if .ref @abs_i .or .ref @abs
@ABS
@ABS_I
      LDY #2
      LDA (@HEAP_PTR),Y ; get high value
      BPL ?ABSPOSITIV

      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG

      jmp @NEG_INNER

;      SEC             ;Ensure carry is set
;      LDA #0          ;Load constant zero
;      SBC @REG+0      ;... subtract the least significant byte
;      TAY             ;... and store the result
;      LDA #0          ;Load constant zero again
;      SBC @REG+1      ;... subtract the most significant byte
;      TAX             ;... and store the result
;      RTS

?ABSPOSITIV
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY
      RTS
;.endif

; MIN a,b
.if .ref @min_ii
@MIN
@MIN_II
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @ERG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @ERG
; (x*256+y) ist der Wert im Heap

      LDY #4
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY

; Bedingung (a>b)
 CPY @ERG
 TXA
 SBC @ERG+1
 BVC ?VC1112
 EOR #$80
?VC1112
 BMI ?A_GT_B2

?MIN_FALSE
 LDY @ERG
 LDX @ERG+1
 RTS

?A_GT_B2
?MIN_TRUE
; LDY @REG
; LDX @REG+1
 RTS
.endif

; MAX a,b
.if .ref @max_ii
@MAX
@MAX_II
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @ERG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @ERG
; (x*256+y) ist der Wert im Heap

      LDY #4
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY

; (x*256+y) ist der Wert im Heap
; STY @REG
; STX @REG+1

; Bedingung (a>b)
 CPY @ERG
 TXA
 SBC @ERG+1
 BVC ?VC111
 EOR #$80
?VC111
 BMI ?A_GT_B

?MAX_FALSE
; LDY @REG
; LDX @REG+1
 RTS

?A_GT_B
?MAX_TRUE
 LDY @ERG
 LDX @ERG+1
 RTS
.endif

; Negiert ein gegebenes Word
; ist das gleiche wie (x*256+y) := (x*256+y) * -1 nur schneller
@NEG
@NEG_I
      LDY #2
      LDA (@HEAP_PTR),Y ; wert holen
      STA @REG+1
      DEY
      LDA (@HEAP_PTR),Y
      STA @REG

; 16 bit Binary Negation
@NEG_INNER
       SEC             ;Ensure carry is set
       LDA #0          ;Load constant zero
       SBC @REG+0      ;... subtract the least significant byte
       TAY             ;... and store the result
       LDA #0          ;Load constant zero again
       SBC @REG+1      ;... subtract the most significant byte
       TAX             ;... and store the result

       RTS

; Convertiert vorzeichenrichtig ein Byte zu einem Word
; Der Compiler koennte es leisten, ist mir aber zu kompliziert
; Beim Ausfuehren weiss das Programm nichts mehr von byte oder word
; kostet hier 19 Takte + 28 Takte (init)
.if .ref @toword_i
@TOWORD
@TOWORD_I
      LDY #1            ;2
      LDA (@HEAP_PTR),Y ;5 wert holen (ein Byte)

      BMI ?NEGATIV      ;2 (positiv, no jump)
      TAY               ;2
      LDX #0            ;2
      RTS               ;6

?NEGATIV
      TAY               ;2 + 1 (branch)
      LDX #$FF          ;2
      RTS               ;6
.endif

; liefert 1, wenn das uebergebene ungerade ist
.if .ref @odd_i
@ODD
@ODD_I
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen (ein Byte)
      AND #~00000001
      BNE ?TRUE
      JMP ?FALSE
.endif

; liefert 1, wenn das uebergebene gerade ist
.if .ref @even_i
@EVEN
@EVEN_I
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen (ein Byte)
      AND #~00000001
      BNE ?FALSE
;      BEQ ?TRUE
.endif

?TRUE
      LDY #1
      LDX #0
      RTS

?FALSE
      LDY #0
      LDX #0
      RTS

; TODO: Potenzieren würde 2 Parameter erfordern, wird nicht unterstuetzt. Aber x*x kann jeder selbst tippen

