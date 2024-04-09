; -*- text -*-
;Macros
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2022


; Increment a word value by one
    .MACRO WINC
      INC %1   ; 5
      BNE W    ; 2+1
      INC %1+1 ; 5
W
    .ENDM

    .macro move.b
    lda %1
    sta %2
    .endm

    .macro move.w
    move.b %1,%2
    move.b %1+1,%2+1
    .endm

; decrement a word value by one
    .MACRO WDEC
      LDA %1+0       ;Test if the LSB is zero
      BNE SKIP       ;If it isn't we can skip the next instruction
      DEC %1+1       ;Decrement the MSB when the LSB will underflow
SKIP  DEC %1+0       ;Decrement the LSB
    .ENDM

; @deprecated
; wir coden das jetzt selbst
; Folgendes Macro wird verwendet um den Heap_Ptr zu erhoehen,
; wenn Proceduren mit Parametern aufgerufen werden.
; 11 Bytes (statt 6 Bytes (2+3+1) (lda #, jsr x, rts))
; aber 13 Takte statt 24 mit jsr
    .MACRO ADD_TO_HEAP_PTR
      CLC              ;2 (Takte)
      LDA @HEAP_PTR    ;3
      ADC #%1          ;2
      STA @HEAP_PTR    ;3
      BCC NO_INC_HIGH_HEAP_PTR ;3 ; => 13 Takte statt 24 mit jsr

      INC @HEAP_PTR+1  ;5

NO_INC_HIGH_HEAP_PTR
    .ENDM


; @deprecated
; wir coden das jetzt selbst
; Folgendes Macro wird verwendet um den Heap_Ptr zu erniedrigen,
; wenn Proceduren mit Parametern aufgerufen wurden.
; 11 Bytes (statt 6 Bytes (2+3+1) (lda #1, jsr x, rts))
; aber 13 Takte statt 32 mit jsr
    .MACRO SUB_FROM_HEAP_PTR
      SEC              ;2
      LDA @HEAP_PTR    ;3
      SBC #%1          ;2
      STA @HEAP_PTR    ;3
      BCS NO_DEC_HIGH_HEAP_PTR ;3 ; => 13 Takte statt 30 mit jsr

      DEC @HEAP_PTR+1  ;5

NO_DEC_HIGH_HEAP_PTR
    .ENDM

; To store a word value into a word array, we use @PUTARRAY Pointer
; to support more optimizations, we use (A + 256 * X) here
; first we need to multiply pointer by 2, then add variable
; Putarrayw Var
    .MACRO PUTARRAYW
;      TYA         ; 0 putarrayw MACRO
      ASL A       ; 2 Mult (x,y)*2
      TAY         ; 2
      TXA         ; 2
      ROL A       ; 2
      TAX         ; 2
      CLC         ; 2 add %1 to the nth value
      TYA         ; 2
      ADC # <%1   ; 2
      STA @PUTARRAY ; 3
      TXA         ; 2
      ADC # >%1   ; 2
      STA @PUTARRAY+1 ; 3
    .ENDM
;         in Summe 26 Zyklen 16 Bytes


; To get a word value from a word array, we use @GETARRAY pointer
; to support some more optimizations we use (A + 256 * X) for set pointer
; first we need to multiply pointer by 2, then add variable
; and get the result in akku, extern we need to move it to Y-Register
; Getarrayw Var
    .MACRO GETARRAYW
;      TYA           ; 0 Getarrayw MACRO
      ASL A         ; 2 Mult (x,y)*2
      TAY           ; 2
      TXA           ; 2
      ROL A         ; 2
      TAX           ; 2
      CLC           ; 2 add %1 to the nth value
      TYA           ; 2
      ADC # <%1     ; 2
      STA @GETARRAY ; 3
      TXA           ; 2
      ADC # >%1     ; 2
      STA @GETARRAY+1 ; 3
      LDY #1        ; 2 load x and y from @ARRAY
      LDA (@GETARRAY),Y ; 5
      TAX           ; 2
      DEY           ; 2
      LDA (@GETARRAY),Y ; 5
;      TAY           ; 0
    .ENDM
;          in Summe 42 Zyklen 23 Bytes

 .BANK
 .SET 6,0

; lot of variables in the zero page
;
; Multisprites use the Zeropage Register from $80 - $89
;
;
 *=$0090 ; 144

;
;           OO                              OO
;  OOOOO  OOOOOOO OOOOOO  OO   OO  OOOOO  OOOOOOO OO   OO OOOOOO   OOOOO
; OO        OO    OO   OO OO   OO OO   OO   OO    OO   OO OO   OO OO   OO
;  OOOOO    OO    OO      OO   OO OO        OO    OO   OO OO      OOOOOOO
;      OO   OO    OO      OO   OO OO   OO   OO    OO   OO OO      OO
;  OOOOO     OOOO OO       OOOOOO  OOOOO     OOOO  OOOOOO OO       OOOOO
;

@show_screen
 .byte 0

@countOfEnteredFloor
  .byte 0

@countOfEnterableFloors
  .byte 0

; where the key for the door will arrive
@key_screen
 .word 0

@door_screen
 .word 0

@door_color
 .byte 0

@waitForEnemyAnimation
 .byte 0

; this is a calculation variable in Dude, very often used
@screen
 .word 0

@dude_xpos
 .byte 0

@dude_ypos
 .byte 0

@enemy_type
 .byte 0

@enemy_index
 .byte 0

@arrow_index
 .byte 0

@enemy_to_draw
 .byte 0

;
; The Sound Hexen Player use the Zeropage Register 203-211 so we must < 203!
;
  .if * >= 203
    .error "Memory overflow in ZERO page! * must < 203 see MACROS.INC here"
  .endif



; Set Color hard in shadow register
;
 *=708
 .byte $06 ; 708
 .byte $08 ; 709
 .byte $0A ; 710
 .byte $0C

; Text we want to display at loading
;
 *=$0129                     ; Makes us compatible with Hias OS
?dlist_line
  .sbyte "    L"
  .sbyte +$40,"O"
  .sbyte +$80,"A"
  .sbyte +$C0,"D"
  .sbyte +$80,"I"
  .sbyte +$40,"N"
  .sbyte "G.        "


; very small Displaylist to show loading
;
 *=$3c0 ; we use the 40 bytes of the printer buffer here
?dlist_loading
 .byte DL_E8,DL_E8,DL_E8
 .byte DL_E8,DL_E8,DL_E8,DL_E8
 .byte DL_GR1|DL_ADDRES
 .word ?dlist_line                 ; wir zwacken 20 Bytes vom Stack ab ;-)
 ; Displaylist must be full length
 .byte DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8
 .byte DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8,DL_E8

 .byte DL_LOOP
 .word ?dlist_loading

  .if * >= 1000
    .error "Memory overflow in printer buffer! * must < 1000"
  .endif

; Displaylist activate by set into shadow registers
;
 *=560
 .word ?dlist_loading

;
; OO      OOOO   OOOO  OOOOO  OOOO OO  OO  OOOO
; OO     OO  OO OO  OO OO  OO  OO  OOO OO OO  OO
; OO     OO  OO OO  OO OO  OO  OO  OOOOOO OO
; OO     OO  OO OO  OO OO  OO  OO  OO OOO OO
; OO     OO  OO OO  OO OO  OO  OO  OO  OO OO OOO
; OO     OO  OO OOOOOO OO  OO  OO  OO  OO OO  OO  O  O  O
; OOOOOO  OOOO  OO  OO OOOOO  OOOO OO  OO  OOOO   O  O  O
;

; Der Loading Font, es sind nur die Zeichen hier belegt, die gebraucht werden fuer die Darstellung
;
*=$be00
?loading_font
 .dc 112 0

 .byte ~00000000 ; ...
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~00000000
 .byte ~01001001
 .byte ~01001001
 .byte ~00000000

 .dc 136 0
 .dc 8 0

; LOADING

 .byte ~00011000 ; A
 .byte ~00111100
 .byte ~01100110
 .byte ~01100110
 .byte ~01111110
 .byte ~01100110
 .byte ~11110110
 .byte ~00000000

 .dc 8 0
 .dc 8 0

 .byte ~11111000 ; D
 .byte ~01101100
 .byte ~01100110
 .byte ~01100110
 .byte ~01100110
 .byte ~01100110
 .byte ~11111100
 .byte ~00000000

 .dc 8 0
 .dc 8 0

 .byte ~00111110 ; G
 .byte ~01100010
 .byte ~11000000
 .byte ~11001100
 .byte ~11000110
 .byte ~01100110
 .byte ~00111100
 .byte ~00000000

 .dc 8 0

 .byte ~00111100 ; I
 .byte ~00011000
 .byte ~00011000
 .byte ~00011000
 .byte ~00011000
 .byte ~00011000
 .byte ~00111100
 .byte ~00000000

 .dc 8 0
 .dc 8 0

 .byte ~11110000 ; L
 .byte ~01100000
 .byte ~01100000
 .byte ~01100000
 .byte ~01100000
 .byte ~01100010
 .byte ~11111110
 .byte ~00000000

 .dc 8 0

 .byte ~11100110 ; N
 .byte ~01110110
 .byte ~01111110
 .byte ~01111110
 .byte ~01101110
 .byte ~01100110
 .byte ~11110110
 .byte ~00000000

 .byte ~00111100 ; O
 .byte ~01101110
 .byte ~01100110
 .byte ~01100110
 .byte ~01100110
 .byte ~01110110
 .byte ~00111100
 .byte ~00000000

; Kurze Pause erzwingen, damit LOADING auch wirklich gezeigt wird
; Platte dreht mit 288 upm, also alle 5f einmal

@init_wait_for_font
 lda #>?loading_font
 sta chbas
 sta chbase
;
; Nice to know, how to stop Disk Tone, but most Atarians love this disk sound
; lda #0
; sta soundr

 ldx #3
?loop2
 lda 20
?loop
 cmp 20
 beq ?loop
 dex
 bne ?loop2
 rts

 .bank

 *=$02e2
 .word @init_wait_for_font

; Interrupt Routinen in
 *=$580
 .include "SIMPLE-64K.INC"

  .if * > $5ff
    .error "Memory overflow in SIMPLE-64K buffer! * must < $5ff"
  .endif

;
; OOOOO                OOO                    OO
; OO  OO                OO                    OO
; OO  OO OOOOO   OOOO   OO   OOOO   OOOOO  OOOOO  OOOO  OOOOO
; OO  OO OO  OO OO  OO  OO  OO  OO OO  OO OO  OO OO  OO OO  OO
; OOOOO  OO     OOOOOO  OO  OO  OO OO  OO OO  OO OOOOOO OO
; OO     OO     OO      OO  OO  OO OO  OO OO  OO OO     OO
; OO     OO      OOOO  OOOO  OOOO   OOOOO  OOOOO  OOOO  OO
;
;
; The data, we would move under Atari OS, must be loaded at first time.
; We load it into memory $4000 - $8000
; switch OS away (RAM occur)
; move the data
; switch OS back
; load the rest

?all_playfield_data_blob=$4000
 *=$4000-6
 .incbin "ALL-PLAYFIELDS.DAT"

 .if * >= $7ffa
   .error "Memory overflow in comprimized data! * must < $8000 see MACROS.INC here"
 .endif

?last_byte
?FROM=212
?TO=214
?SIZEL=216
?SIZEH=217

 *=$8000

@init_playfields
; Damit es nicht flackert, wenn wir das OS abschalten, kopieren wir noch einen Font
; lda #0
; ldx chbas
; sta ?FROM
; stx ?FROM+1
;
; lda #<$bc00
; ldx #>$bc00
; sta ?TO
; stx ?TO+1
;
; lda #<1024
; ldx #>1024
; sta ?sizel
; stx ?sizeh

; jsr ?movedown

; lda #$bc
; sta chbas
; sta CHBASE

; lda 20
;?loop
; sta WSYNC
; cmp 20
; beq ?loop

 jsr @INIT_SIMPLE_64K           ; init 64kb und activate RAM

 lda #<?all_playfield_data_blob
 ldx #>?all_playfield_data_blob
 sta ?FROM
 stx ?FROM+1

 lda #<$C000
 ldx #>$C000
 sta ?TO
 stx ?TO+1

 lda #<$0fff
 ldx #>$0fff
 sta ?sizel
 stx ?sizeh

 jsr ?movedown

 lda #<$5800
 ldx #>$5800
 sta ?FROM
 stx ?FROM+1

 lda #<$d800
 ldx #>$d800
 sta ?TO
 stx ?TO+1

 lda #<$27f9 ; maximale size ~10kb, the last 6 bytes MUST NOT overwritten
 ldx #>$27f9
 sta ?sizel
 stx ?sizeh

 jsr ?movedown

 jsr @ACTIVATE_ROM

; copy der Daten sollte durch sein, jetzt weitere Daten laden
 rts

; FROM = source start address
;   TO = destination start address
; SIZE = number of bytes to move
;
?MOVEDOWN LDY #0
         LDX ?SIZEH
         BEQ ?MD2

?MD1     LDA (?FROM),Y ; move a page at a time
         STA (?TO),Y
         INY
         BNE ?MD1
         INC ?FROM+1
         INC ?TO+1
         DEX
         BNE ?MD1

?MD2     LDX ?SIZEL
         BEQ ?MD4

?MD3     LDA (?FROM),Y ; move the remaining bytes
         STA (?TO),Y
         INY
         DEX
         BNE ?MD3

?MD4     RTS

 .bank
 *=$02e2
 .word @init_playfields

 .BANK
 .SET 6,0
