;FAST_SCREEN_OUTPUT-Library
;-*- text -*-
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2019
;

; zeigt exact auf die Adresse des Cursors
@CURRENT_CURSOR_ROW
 .word 0

   .LOCAL

?PRINTFF_COLOR = @REG+8

; ----------------------------------------------------
; Schnellere Routine um Zeichen in den Bildschirm zu "stoßen"
; Character kommt im Akku!
@FASTSCREEN_OUT
; character ASCII -> Screenbyte umwandeln
; alles <32 with +64
; alles >96 bleibt wie es ist
; alles zw. 32 und 96 with -32

 CMP #32
 BMI ?CHAR_SMALLER_33

 CMP #96
 BPL ?SETFASTCHAR

 SEC
 SBC #32

 JMP ?SETFASTCHAR

?CHAR_SMALLER_33
 CLC
 ADC #64

?SETFASTCHAR
; Ab hier ist das Char ein Screenbyte

 CMP #$9b     ; Sonderzeichen, carrige return
 BEQ ?CURSOR_NEXTLINE

 ORA ?PRINTFF_COLOR
; TAX
 LDY COLCRS
; TXA
 STA (@REG+6),Y

; Ab hier cursor Movement
 INY
 CPY ?BYTES_PER_LINE
 BPL ?CURSOR_NEXTLINE

 STY COLCRS

 LDY #0               ; error code!
 LDX #0
 RTS


?CURSOR_NEXTLINE
 LDA #0
 STA COLCRS

 INC ROWCRS

 CLC
 LDA @REG+6
 ADC ?BYTES_PER_LINE
 STA @REG+6
 STA @CURRENT_CURSOR_ROW
 BCC ?NO_INC_HIGH2

 INC @REG+7
 INC @CURRENT_CURSOR_ROW+1

?NO_INC_HIGH2
 LDY #0              ; error code!
 RTS


?BYTES_PER_LINE
 .byte 20

; Zeigt auf die linke obere Ecke, INIT_FASTSCREEN setzt das!
?SCREEN_UPPER_LEFT
 .word 0

;.if .ref @init_fastscreen_i

; setzt die linke obere Ecke
@INIT_FASTSCREEN
@INIT_FASTSCREEN_I
     LDY #2
     LDA (@HEAP_PTR),Y
     STA ?SCREEN_UPPER_LEFT+1
     STA @CURRENT_CURSOR_ROW+1

     DEY
     LDA (@HEAP_PTR),Y
     STA ?SCREEN_UPPER_LEFT
     STA @CURRENT_CURSOR_ROW

     DEY            ; save a byte
     STY COLCRS     ; set colcrs to 0
     STY ROWCRS     ; set rowcrs to 0

; Der default ist 20 bytes
     LDA #20
?set_bytes_per_line
     STA ?BYTES_PER_LINE

     RTS
;.endif

; setzt die Anzahl an Bytes pro Zeile. Nach INIT_FASTSCREEN setzen!
; folgende Breiten gibt es
; 16 Gfx 1&2 und 559<=Schmalles Anzeigefeld
; 20 Gfx 1&2
; 24 Gfx 1&2 und 559<=breites Anzeigefeld oder horiz. Scrolling
; 28 Gfx 1&2 und 559<=breites Anzeigefeld und horiz. Scrolling
; 32 Gfx 0 und schmalles Anzeigefeld
; 40 Gfx 0
; 48 Gfx 0 und 559<=breites Anzeigefeld oder horiz. Scrolling

;.if .ref @init_set_bytes_per_line_i
@INIT_SET_BYTES_PER_LINE
@INIT_SET_BYTES_PER_LINE_I
     LDY #1
     LDA (@HEAP_PTR),Y
     JMP ?set_bytes_per_line

@FAST_GOTOXY_CLEAR
 LDA #0
 sta COLCRS
 jmp ?inner_fast_gotoxy

; bewegt den Cursor an eine andere Position (0,y)
@FAST_GOTOY
@FAST_GOTOY_I
 LDA #0
 STA COLCRS

 LDY #1
 LDA (@HEAP_PTR),Y
 jmp ?inner_fast_gotoxy

;.endif

; bewegt den Cursor eine Position nach unten
; man ist fuer den overrun selbst zustaendig!
; TODO: @fast_gotoy_next() DOES NOT WORK AS EXPECTED!
;@FAST_GOTOY_NEXT
; lda #0
; sta colcrs
; ldy rowcrs
; iny
; tya
; jmp ?inner_fast_gotoxy

; bewegt den Cursor an eine andere Position (x, y)
; und berechnet dabei die NEXT_CURSOR_POSITION neu
; WICHTIG, INIT_FASTSCREEN muss gerufen worden sein
;.if .ref @fast_gotoxy_ii
@FAST_GOTOXY
@FAST_GOTOXY_II
 LDY #1
 LDA (@HEAP_PTR),Y
 STA COLCRS
; X-position wird spaeter addiert

 LDY #3
 LDA (@HEAP_PTR),Y

; innerer Einsprung, erwartet die Y-Position im Akku
?inner_fast_gotoxy
 STA ROWCRS
 TAY

 LDA ?SCREEN_UPPER_LEFT
 STA @CURRENT_CURSOR_ROW
 LDA ?SCREEN_UPPER_LEFT+1
 STA @CURRENT_CURSOR_ROW+1

 CPY #0
 BEQ ?NO_INC_OF_LINES

; Y-Cursor * n * Bytes_per_line
  sty @op
  lda ?bytes_per_line
  sta @op+1

  jsr ?mul8

  clc
  tya
  adc ?screen_upper_left
  sta @current_cursor_row
  txa
  adc ?screen_upper_left+1
  sta @current_cursor_row+1
?NO_INC_OF_LINES
  rts

; https://codebase64.org/doku.php?id=base:short_8bit_multiplication_16bit_product
; (x*256 + y) = @op * (@op+1)
?MUL8
        lda #$00
        ldy #$08
        clc
?m0     bcc ?m1
        clc
        adc @OP+1
?m1     ror
        ror @OP
        dey
        bpl ?m0

        ldy @OP
        tax
        rts

;.endif

;.if .ref @fast_gotox_i
@FAST_GOTOX
@FAST_GOTOX_I
 LDY #1
 LDA (@HEAP_PTR),Y
 STA COLCRS
 RTS
;.endif

;?LOOP
; CLC
; LDA @CURRENT_CURSOR_ROW
; ADC ?BYTES_PER_LINE
; STA @CURRENT_CURSOR_ROW
; BCC ?NO_INC_HIGH
; INC @CURRENT_CURSOR_ROW+1
;?NO_INC_HIGH
; DEY
; BNE ?LOOP
;
;?NO_INC_OF_LINES
; RTS

