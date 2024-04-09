; -*- text -*-
;PRINTF-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;

    .LOCAL

?CURRENT_HEAP
 .byte 0

 .IF .DEF @FASTSCREEN_OUT
@printfd
@printfd_i
@printfd_ii
@printfd_iii
@printfd_iiii
@printfd_iiiii
@printfd_iiiiii
@printfd_iiiiiii
@printfd_iiiiiiii

 LDY #'D
 STY @PRINTF_TYPE
 JMP ?printff_entry

; Einfachere Version von @printf('F', ...
@printff
@printff_i
@printff_ii
@printff_iii
@printff_iiii
@printff_iiiii
@printff_iiiiii
@printff_iiiiiii
@printff_iiiiiiii

 LDY #'F
 STY @PRINTF_TYPE

?printff_entry
 LDY #2            ; erster Parameter, Adresse des Arrays
 STY ?CURRENT_HEAP ; wir muessen uns den Heap merken, da wir auf die naechsten Werte zugreifen wollen
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX
 DEY               ;
 LDA (@HEAP_PTR),Y ; low Wert holen
 TAY

; muss ueber INIT_FASTSCREEN initialisiert werden
; wird auch von FAST_GOTOXY manipuliert
; wird hier einmal gesetzt und dann genutzt
 LDA @CURRENT_CURSOR_ROW
 STA @REG+6
 LDA @CURRENT_CURSOR_ROW+1
 STA @REG+7

 JMP ?PRINTF_EDITOR_OUTPUT
 .ENDIF

  .IF .DEF @STRING_OUT
; Einfachere Version von @printf('F', ...
@strprintf
@strprintf_ii
@strprintf_iii
@strprintf_iiii
@strprintf_iiiii
@strprintf_iiiiii
@strprintf_iiiiiii
@strprintf_iiiiiiii

 LDY #'S
 STY @PRINTF_TYPE

 LDY #1            ; erster Parameter, Adresse des Strings
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+6
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+7

 LDY #4            ; zweiter Parameter, Adresse des Arrays
 STY ?CURRENT_HEAP ; wir muessen uns den Heap merken, da wir auf die naechsten Werte zugreifen wollen
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX
 DEY               ;
 LDA (@HEAP_PTR),Y ; low Wert holen
 TAY

 JSR ?PRINTF_EDITOR_OUTPUT

 LDA #255
 JMP @STRING_OUT
  .ENDIF


?PRINTFF_COLOR = @REG+8

; Einfache Implementierung eines printf wie wir es von C gewohnt sind
; als erstes der format-String, dann beliebig viele Zeichen,
; TODO: Vorsicht bei mehr als 8 Parametern, muss erst geprueft werden, sollte aber gehen weil Heap
; %s - String
; %d - Zahl mit Vorzeichen -32768 - 32767
; %D - Zahl ohne Vorzeichen 0 - 65535
; %c - Character
; %x - Zahl als 2 Zeichen Hexadezimalwert 0-255 ohne f?hrendes $
; %X - Zahl als 4 Zeichen Hexadezimalwert 0-65535 ohne f?hrendes $
; %% - Prozent ausgeben
; \n - Return ausgeben
; \\ - Backslash ausgeben
; \0-\3 - Farbenadd setzen
; WICHTIG: Wenn der erste Wert kleiner als 255 ist, also X==0 dann als Kanal interpretieren

@printf
@printf_i
@printf_ii
@printf_iii
@printf_iiii
@printf_iiiii
@printf_iiiiii
@printf_iiiiiii
@printf_iiiiiiii

 LDY #2            ; erster Parameter, Adresse des Arrays
 STY ?CURRENT_HEAP ; wir muessen uns den Heap merken, da wir auf die naechsten Werte zugreifen wollen
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX
 DEY               ;
 LDA (@HEAP_PTR),Y ; low Wert holen
 TAY

 CPX #0
 BNE ?PRINTF_EDITOR_OUTPUT

; im ersten Parameter kam ein Wert < 256 und somit holen wir den Formatstring erneut.
 STY @PRINTF_TYPE

 LDY #4            ; erster Parameter, Adresse des Arrays
 STY ?CURRENT_HEAP ; wir muessen uns den Heap merken, da wir auf die naechsten Werte zugreifen wollen
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX
 DEY               ;
 LDA (@HEAP_PTR),Y ; low Wert holen
 TAY

?PRINTF_EDITOR_OUTPUT
 STY @REG+2  ; Wir verwenden @REG+2, weil @REG in einigen SCREEN_OUTPUT Routinen verwendet wird
 STX @REG+3

; CLC               ; 2
; LDA ?CURRENT_HEAP ; 4
; ADC #2            ; 2
; STA ?CURRENT_HEAP ; 4
 INC ?CURRENT_HEAP  ; 6
 INC ?CURRENT_HEAP  ; 6

 LDA #0
 STA ?PRINTFF_COLOR

; solange Zeichen ausgeben, bis ein $FF kommt
 LDY #0
?PRINTF_LOOP
 LDA (@REG+2),Y
 INY
 STY @REG+4

 CMP #$FF             ; $FF gefunden?
 BEQ ?NO_MORE_CHARS

 CMP #'\              ;\ gefunden aktuell nur \n
 BEQ ?SLASH_FOUND

 CMP #'%              ;% gefunden, aktuell %d %D %X % x %s %c
 BEQ ?PERCENT_FOUND

?PRINTF_OUTPUT        ; Zeichen einfach ausgeben
; ORA ?PRINTFF_COLOR
 JSR @SCROUT

 STY ?ERROR_CODE
 CPY #127
 BCS ?ERROR_OCCURED

?NOCHAR_OUTPUT
 LDY @REG+4
 BNE ?PRINTF_LOOP

?NO_MORE_CHARS
 LDY #0

?ERROR_OCCURED
 LDX #0
 STX @PRINTF_TYPE
 RTS

?ERROR_CODE
 .byte 0

; we found a \ in the String --------------------------
?SLASH_FOUND
 LDA (@REG+2),Y
 INY
 STY @REG+4
 CMP #'\ ;\
 BEQ ?PRINTF_OUTPUT ; ein '\' ausgeben

 CMP #'n
 BNE ?PRINTF_NO_N

 LDA #$9B
 JMP ?PRINTF_OUTPUT ; ist ein '\n' somit Return ausgeben

?PRINTF_NO_N
 CMP #'1
 BNE ?PRINTF_NO_1

 LDA #64
 STA ?PRINTFF_COLOR
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_1
 CMP #'2
 BNE ?PRINTF_NO_2

 LDA #128
 STA ?PRINTFF_COLOR
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_2
 CMP #'3
 BNE ?PRINTF_NO_3

 LDA #192
 STA ?PRINTFF_COLOR
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_3
 CMP #'0
 BNE ?PRINTF_NO_0

 LDA #0
 STA ?PRINTFF_COLOR
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_0
 JMP ?PRINTF_OUTPUT ; kein 'n' somit erstmal ausgeben, TODO: Hier weitere Zeichen, tabulator?

; we found a '%' in the String ------------------------
?PERCENT_FOUND
 LDA (@REG+2),Y
 INY
 STY @REG+4
 CMP #'%
 BEQ ?PRINTF_OUTPUT ; ein '%' ausgeben

 CMP #'x                  ; %x 2 Zeichen als hex zahl ausgeben
 BNE ?PRINTF_NO_SHORT_X

 JSR ?GET_CURRENT_HEAP
 JSR @PRINTF_PRINTHEX2
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_SHORT_X

 CMP #'d                  ; %d vorzeichen behaftete Zahl
 BNE ?PRINTF_NO_D

 JSR ?GET_CURRENT_HEAP
 JSR @PRINTF_PRINTVALUE
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_D

 CMP #'D                  ; %D nicht vorzeichenbehaftete Zahl
 BNE ?PRINTF_NO_BIG_D

 JSR ?GET_CURRENT_HEAP
 JSR @PRINTF_PRINTDIGITS
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_BIG_D

 CMP #'s                  ; %s String ausgeben
 BNE ?PRINTF_NO_S

 JSR ?GET_CURRENT_HEAP
 JSR @PRINTF_PRINTSTRING
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_S

 CMP #'X                  ; %X 4 zeichen als hex Zahl ausgeben
 BNE ?PRINTF_NO_BIG_X

 JSR ?GET_CURRENT_HEAP
 JSR @PRINTF_PRINTHEX4
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_BIG_X

 CMP #'c                  ; %c Character ausgeben
 BNE ?PRINTF_NO_C

 JSR ?GET_CURRENT_HEAP
 JSR @PRINTF_PRINTCHAR
 JMP ?NOCHAR_OUTPUT

?PRINTF_NO_C

 JMP ?PRINTF_OUTPUT ; kein 'd' somit erstmal ausgeben, TODO: Hier weitere Zeichen

; holt (x*256+y) vom Heap und setzt den Heap Zeiger auf den naechsten Wert
?GET_CURRENT_HEAP
 LDY ?CURRENT_HEAP
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX
 DEY               ;
 LDA (@HEAP_PTR),Y ; low Wert holen
 TAY

 INC ?CURRENT_HEAP
 INC ?CURRENT_HEAP
 RTS

;.if .ref @PRINTF_PRINTHEX2
@PRINTF_PRINTHEX2
      TYA
      JMP @PRINTHEX
;.endif
