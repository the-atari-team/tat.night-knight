;SCREEN_OUTPUT-Library
;-*- text -*-
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2019
;

   .LOCAL

; Hardware-Treibertabellen
; EDITRV = $E400  ; Editor
; SCRENV = $E410  ; Screen
; KEYBDV = $E420  ; Keyboard

; Jeder Treiber sieht wie folgt aus
; 0 Vektor zu OPEN -1
; 2 Vektor zu CLOSE -1
; 4 Vektor zu GETBYTE -1
; 6 Vektor zu PUTBYTE -1
; 8 Vektor zu STATUS -1
; 10 Vektor zu SPECIAL -1
; 12 JMP ($4c)
; 13 Adresse zur INIT Routine
; 15 unbenutzt

; ----------------------------------------------------
; Wichtige Routinen hier:
; @PRINTSTRING  gibt uebergebenen String aus (adr:bytearray)
; @PRINTCHAR    gibt ein Zeichen aus
; @PRINTVALUE   gibt eine Zahl vorzeichenbehaftet aus
; @PRINTDIGITS  gibt eine Zahl nicht vorzeichenbehaftet aus
; @CLRSCR       loescht den Schirm, alles was in der Displaylist erreichbar ist, leider auch den Header :-(
; @PRINTHEX2    gibt eine Zahl hexadezimal aus, 2 Zeichen only
; @PRINTHEX4    gibt eine Zahl hexadezimal aus, 4 Zeichen, Reihenfolge ist fuer die Ausgabe richtig, gross zuerst
;
; write ln() ist ausgebaut, @printf() verwenden!
; @PRINT_STRING gibt String aus, dieser beginnt sofort hinter dem JSR @PRINT_STRING und endet mit $FF
; @EOLOUT       gibt ein Atari-Return aus
; @DECOUT       gibt eine Zahl nicht vorzeichenbehaftet aus (x*256+y)
; @SCROUT       gibt ein Zeichen aus (aus Akku)

?PRINTFF_COLOR = @REG+8

; ----------------------------------------------------
; Hier nur Routinen, die Dinge auf dem Screen ausgeben
; ----------------------------------------------------

.if .ref @clrscr
; Loesche den Bildschirm
@CLRSCR
      LDA EDITRV+1
      PHA
      LDA EDITRV
      PHA
      RTS
.endif

; ----------------------------------------------------
; Zeichenfolge auf Screen ausgeben
; endet mit $FF
;.if .ref @print_string
@PRINT_STRING
      LDX #0
      STX ?PRINTFF_COLOR
      PLA
      STA @AUX
      PLA
      STA @AUX+1
      WINC  @AUX

      JSR ?PRINT_AUXCONTENT

      LDA @AUX+1
      PHA
      LDA @AUX
      PHA
      RTS
;.endif

; ----------------------------------------------------
; Cursor in neue Zeile (enter)
@EOLOUT
      lda #0
      sta ?printff_color
      LDA #$9B  ;EOL ausgeben
      BNE @SCROUT

; @PRINTCHAR fuer Ausgabe eines Zeichens, nutzt die Funktion @SCROUT
@PRINTCHAR
@PRINTCHAR_I
     ldx #0
     stx ?printff_color
     LDY #1
     LDA (@HEAP_PTR),Y

;       EIN Zeichen ausgeben
; <A> : auszugebendes Zeichen
; PRINTF_TYPE gibt den Canal an, auf dem die Daten ausgegeben werden sollen
; PRINTF_TYPE == 'F' FAST output, damit es auch wirklich flotter geht, erster Test
; PRINTF_TYPE == 0  EDITRV, Ausgabe auf Canal 0 == E: der eingebaute Editor
; PRINTF_TYPE == 6  SCREENOUT, ein Graphics Output Device
; PRINTF_TYPE < 8   0-7 und nicht 0 und nicht 6, Gibt Daten per CIOV aus
; PRINTF_TYPE == 'D' Deviate Output, kann man selbst den Output etwas decorieren
; PRINTF_TYPE == 'S' String Output, schreibt die Daten in einen String
@SCROUT
      TAY

      LDA @PRINTF_TYPE

 .IF .DEF @FASTSCREEN_OUT
      CMP #'F
      BNE ?NO_FASTSCREEN_OUT

      TYA
      JMP @FASTSCREEN_OUT
 .ENDIF

?NO_FASTSCREEN_OUT
      CMP #0
      BEQ ?EDITOR_OUT
      CMP #6
      BEQ ?SCREEN_OUT
      cmp #8
      bcc ?CIOV_OUT


 .IF .DEF @DEVIATE_SCREEN_OUT
      CMP #'D
      BNE ?NO_DEVIATE_OUT
      TYA
      JMP @DEVIATE_SCREEN_OUT
 .ENDIF

?NO_DEVIATE_OUT

 .IF .DEF @STRING_OUT
      CMP #'S
      BNE ?NO_STRING_OUT

      TYA
      JMP @STRING_OUT
 .ENDIF
?NO_STRING_OUT


?EDITOR_OUT
      tya
      ORA ?PRINTFF_COLOR
      tay

      LDA EDITRV+7
      PHA
      LDA EDITRV+6
      PHA
      TYA
      RTS

?SCREEN_OUT
      tya
      ORA ?PRINTFF_COLOR
      tay

      LDA SCRENV+7
      PHA
      LDA SCRENV+6
      PHA
      TYA
      RTS

; Nutzt den printf_type als Canal, Atari OS braucht den Wert * 16 im X Register
; Canal muss vorher mittels @OPEN(CANAL,8,0,'...') geoeffnet sein
; Am Ende mittels @Close(CANAL) unbedingt schliessen
?CIOV_OUT
      tya
      ORA ?PRINTFF_COLOR
      tay

      lda @printf_type
      asl
      asl
      asl
      asl
      tax
      lda icput+1,x
      pha
      lda icput,x
      pha
      tya
      rts

@PRINTF_TYPE
 .byte 0

; ----------------------------------------------------
@PRINTF_PRINTCHAR
     TYA
     JMP @SCROUT

; TODO: Cursor-Steuerung?
; up() down() left() right()

; ----------------------------------------------------
; Ausgabe eines Strings per Parameter
;.if .ref @printstring_i
@PRINTSTRING
@PRINTSTRING_I
      LDX #0
      STX ?PRINTFF_COLOR

      LDY #2
@_PRINTSTRING_NEED_YREG
      LDA (@HEAP_PTR),Y ; wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY
;.endif

@PRINTF_PRINTSTRING
      STY @AUX
      STX @AUX+1

;.if .ref ?PRINT_AUXCONTENT
?PRINT_AUXCONTENT
      LDX #0
?PRINT2
      LDA (@AUX,X)
      CMP #$FF
      BEQ ?PREXIT2

      JSR @SCROUT
      WINC  @AUX
      LDX #0
      BEQ ?PRINT2

?PREXIT2
      RTS
;.endif

; ----------------------------------------------------
; @PRINTHEX2 um 2 HEX-Zahlen auszugeben
; '$' muss per @PRINTCHAR(36) ausgegeben werden
;.if .ref @printhex2_i
@PRINTHEX2
@PRINTHEX2_I
      ldx #0
      stx ?printff_color

      LDY #1
      LDA (@HEAP_PTR),Y ; Wert holen
      JMP @PRINTHEX
;.endif

; ----------------------------------------------------
; @PRINTHEX4 um 4 HEX-Zahlen auszugeben (word oder byte)
; '$' muss per @PRINTCHAR(36) ausgegeben werden
;.if .ref @PRINTHEX4_I
@PRINTHEX4
@PRINTHEX4_I
      ldx #0
      stx ?printff_color

;      LDY #2
;      LDA (@HEAP_PTR),Y ; Wert holen
;      TAX
;      DEY
;      LDA (@HEAP_PTR),Y
;      TAY
      jsr ?heap_ptr_to_xy
;      jmp @printf_printhex4
;.endif

@PRINTF_PRINTHEX4
;      STY @REG
      TYA
      PHA
;      STX @REG+1 ; unnoetig
      TXA
      JSR @PRINTHEX
;      LDA @REG
      PLA
;      JMP @PRINTHEX ; unoetig

; Ein Byte in hex ausgeben
; <A> enthaelt das Zeichen
@PRINTHEX
      PHA
      LSR A
      LSR A
      LSR A
      LSR A
      TAX
      LDA @ASCIIHEX,X
      JSR @SCROUT
      PLA
      AND #$0F
      TAX
      LDA @ASCIIHEX,X
      JMP @SCROUT

@ASCIIHEX
      .BYTE '0,'1,'2,'3,'4,'5,'6,'7,'8,'9,'A,'B,'C,'D,'E,'F,$FF

; Wir nutzen hier eine funktion um an XY aus dem Heap_ptr zu kommen
; spart ab der 2. Nutzung ein paar Bytes

?heap_ptr_to_xy
      LDY #2
      LDA (@HEAP_PTR),Y ; Wert holen
      TAX
      DEY
      LDA (@HEAP_PTR),Y
      TAY
      RTS

; @asciihexToInt(hex as string)
; @return position in the hex array, is also the hex value
;.if .ref @ASCIIHEXTOINT_I
@ASCIIHEXTOINT
@ASCIIHEXTOINT_I
    LDY #1
    LDA (@HEAP_PTR),Y ; wert holen
    ldx #0
    ldy #0
?asciihex_loop
    cmp @ASCIIHEX,y
    beq ?hex_found
    cmp #255
    beq ?hex_not_found
    iny
    bne ?asciihex_loop

?hex_not_found
    ldy #0

?hex_found
    rts
;.endif

; ----------------------------------------------------
; Decimalzahl nicht vorzeichenbehaftet ausgeben (-1 => 65535)
;.if .ref @PRINTDIGITS_I
@PRINTDIGITS
@PRINTDIGITS_I
    ldx #0
    stx ?printff_color

;    LDY #2
;    LDA (@HEAP_PTR),Y ; wert holen
;    TAX
;    DEY
;    LDA (@HEAP_PTR),Y
;    TAY
    jsr ?heap_ptr_to_xy
;.endif

@PRINTF_PRINTDIGITS
    JMP @DECOUT

; ----------------------------------------------------
; Vorzeichenbehaftete Decimalzahl ausgeben (-32768 bis 32767)

@PRINTVALUE
@PRINTVALUE_I
      ldx #0
      stx ?printff_color

;      LDY #2
;      LDA (@HEAP_PTR),Y ; wert holen
;      TAX
;      DEY
;      LDA (@HEAP_PTR),Y
;      TAY
      jsr ?heap_ptr_to_xy
;      jmp @printf_printvalue

;.if .ref @PRINTF_PRINTVALUE
@PRINTF_PRINTVALUE
      STY @REG
      STX @REG+1

      LDA #32
      STA ?VORZEICHEN
;
; Wenn Zahl negativ:
      LDA @REG+1
      AND #128
      BEQ ?POSITIV
;
      LDA #'-   ; Negativ!!!
      STA ?VORZEICHEN
;
      LDA @REG  ;Invertieren
      EOR #255
      STA @REG
      LDA @REG+1
      EOR #255
      STA @REG+1
;
       WINC  @REG
;
; Binaer in Dezimal Umrechnung
?POSITIV
      LDY @REG
      LDX @REG+1
      jmp @DECOUT
;.endif

; ----------------------------------------------------
; Zahl als positive Dezimalzahl ausgeben
; Zahl (x * 256 + y)
;.if .ref @DECOUT
@DECOUT
      STY @AUX  ;Parameter
      STX @AUX+1 ;speichern
      LDX #4
?VORBES
      LDA #'0   ;Ausgabebuffer
      STA ?ZIFFER,X ;mit B.-Code
      DEX       ;fuer Null
      BPL ?VORBES ;vorbesetzen

      LDX #0    ;Stellenzaehler
?STELLE
      LDA @AUX+1 ;Zehner-Potenz
      CMP ?DECHI,X ;groesser als
      BNE ?TSTHI ;restlich.Zahl?
      LDA @AUX
      CMP ?DECLO,X
?TSTHI
      BCC ?KLEINER ;Potenz zu gross
; Zehner-Potenz abziehen, Ziffer erhoehen
      SEC
      LDA @AUX  ;die aktuelle
      SBC ?DECLO,X ;Zehnerpotenz
      STA @AUX  ;abziehen
      LDA @AUX+1
      SBC ?DECHI,X
      STA @AUX+1
      INC ?ZIFFER,X ;Ziffer erhoehen
      JMP ?STELLE ;gleiche Stelle nochmal
; kleinere Zehnerpotenz anwaehlen
?KLEINER
      INX       ;schon vier Stellen
      CPX #4    ;bearbeitet?
      BNE ?STELLE ;nein ->
; nur noch Einerstelle da
      CLC       ;Einerstelle
      LDA @AUX  ;in Ausgabebuffer
      ADC ?ZIFFER+4 ;addieren
      STA ?ZIFFER+4

      LDA ?VORZEICHEN ;Vorzeichen?
      CMP #32
      BEQ ?NO_VORZEICHEN ;--> Nein

      JSR @SCROUT

; fuehrende '0 ueberspringen
?NO_VORZEICHEN
      LDX #0
?ZIFCHECK
      LDA ?ZIFFER,X
      CMP #'0
      BNE ?ZIFPRINT ;--> wenn nicht 0 ausgabe beginnen

      INX       ;am Ende?
      CPX #4
      BNE ?ZIFCHECK
;
?ZIFPRINT
      TXA
      PHA
      LDA ?ZIFFER,X
      JSR @SCROUT ;Print Ziffer
      PLA
      TAX
      INX
      CPX #5    ;am Ende?
      BNE ?ZIFPRINT

      LDA #32
      STA ?VORZEICHEN

      RTS

; zu Debugzwecken wieder ausmarkieren
; PRINT_ZIFFERN
;       JSR @PRINT_STRING

?VORZEICHEN
    .BYTE " "
?ZIFFER
    .BYTE ".....",$FF

; Tabellen der Zehnerpotenzen
; getrennte Tabellen f. LSB und MSB
?DECLO
    .BYTE  <10000, <1000,100,10
?DECHI
    .BYTE  >10000, >1000,0,0
;.endif

; @POSITION(x,y) oder @gotoxy(x,y) um Cursor zu positionieren
;.if .ref @gotoxy_ii .or .ref @position_ii
@gotoxy
@gotoxy_ii
@Position
@Position_ii
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen
      STA COLCRS
      INY
      LDA (@HEAP_PTR),Y
      STA COLCRS+1

      INY
      LDA (@HEAP_PTR),Y ; wert holen
      STA ROWCRS
      RTS
;.endif

; position the cursor only in horizonal position
;.if .ref @gotox_i
@gotox
@gotox_i
      LDY #1
      LDA (@HEAP_PTR),Y ; wert holen
      STA COLCRS
      INY
      LDA (@HEAP_PTR),Y
      STA COLCRS+1
      RTS
;.endif
