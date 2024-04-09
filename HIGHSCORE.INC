; Current score and high score for Night Knight

      .local

; Wir arbeiten hier mit BCD Zahlen, dann haben wir es bei der Ausgabe einfacher
; einfach als Hex-Zahlen (3x1 Byte) rueckwaerts ausgeben
; Das heisst aber:
; in Interrupts ist unbedingt CLD zu verwenden, sollte ADC/SBC zum Einsatz kommen
;
; Da @printff('%x%x%x%x', a,b,c,d) zu teuer ist (sehr viele Bildschirmzeilen),
; implementieren wir das Setzen der (High-)Scores hier einfach nochmal.
; Das setzen geht damit recht flott, Y:=@current_cursor_row) X:=colcrs
; Der Wert @current_cursor_row kommt aus FAST_SCREEN_OUTPUT
;
;
; WICHTIG: Da wir hier BCD nutzen, den Wert hier als hex uebergeben,
; aber nur die Zahlen 0-9 sind zulaessig. Max $9999 ist moeglich!
; erhoehe Highscore um Wert aus Parameter
; Wenn
@ADD_CURRENT_SCORE
@ADD_CURRENT_SCORE_I
 LDY #1
 LDA (@HEAP_PTR),Y ; wert holen
 sta @reg
 iny
 lda (@heap_ptr),y
 sta @reg+1

; lda @pacman_multiply_score_10
; beq ?no_mult
;
; asl @reg      ; um 4 bit verschieben, entspricht in BCD * 10
; rol @reg+1
; asl @reg
; rol @reg+1
; asl @reg
; rol @reg+1
; asl @reg
; rol @reg+1
;
;?no_mult
 SED
 CLC
 lda @reg
 ADC @BCD_CURRENT_SCORE
 STA @BCD_CURRENT_SCORE

 lda @reg+1
 ADC @BCD_CURRENT_SCORE+1
 STA @BCD_CURRENT_SCORE+1

 bcc ?no_upper_score         ; no need to add something to next values

 LDA @BCD_CURRENT_SCORE+2
 ADC #$00
 STA @BCD_CURRENT_SCORE+2

 bcc ?no_upper_score         ; no need to add something to next values

 LDA @BCD_CURRENT_SCORE+3
 ADC #$00
 STA @BCD_CURRENT_SCORE+3

; check for extra live every 10000 points
; inc @lives
; inc @live_update
; TODO: flash wenn wir die 10000 ueberschreiten

?no_upper_score
 CLC
 lda @reg
 ADC bcd_check_score
 STA bcd_check_score

 lda @reg+1
 ADC bcd_check_score+1
 STA bcd_check_score+1

 bcc ?no_upper_check_score         ; no need to add something to next values

 lda bcd_check_score+2
 ADC #0
 STA bcd_check_score+2

?no_upper_check_score
; CLD
; RTS

; check if score greater or equal (parameter)
; return 1 if greater than given parameter
;@CHECK_SCORE_GE_I
;  SED

;  LDY #2
;  LDA (@HEAP_PTR),Y ; wert holen
;  tax
;  dey
;  lda (@heap_ptr),y
;  tay

; bcd_check_score == (x*256+y)
;  cmp bcd_check_score
;  bne ?false_ge
;  cpy bcd_check_score+1
;  beq ?false_ge
;  cpx bcd_check_score+2
;  beq ?true

; bcd_check_score >= (x*256+y)
;?false_ge
  lda bcd_check_score
  CMP bcd_new_live
  LDA bcd_check_score+1
  SBC bcd_new_live+1
  LDA bcd_check_score+2
  SBC bcd_new_live+2
  BCC ?false

?true
 inc @lives
 inc @live_update
; TODO: flash wenn wir die 10000 ueberschreiten

; ?SUB_CHECK_SCORE
;  SED
;  LDY #1
;  LDA (@HEAP_PTR),Y ; wert holen
;  sta @reg
;  iny
;  lda (@heap_ptr),y
;  sta @reg+1

  SEC
  LDA bcd_check_score
  SBC bcd_new_live
  STA bcd_check_score

  LDA bcd_check_score+1
  SBC bcd_new_live+1
  STA bcd_check_score+1

  LDA bcd_check_score+2
  SBC #$00
  STA bcd_check_score+2

  LDA bcd_check_score+3
  SBC #$00
  STA bcd_check_score+3

  CLD
  ldy #1
  ldx #0
  RTS

?false
  CLD
  ldy #0
  ldx #0
  rts


; ueberprueft current score mit Highscore und kopiert wenn current > high
@CHECK_FOR_NEW_HIGHSCORE
 LDA @BCD_CURRENT_SCORE+3
 CMP @BCD_HIGHSCORE+3
 BMI ?DO_NOT_COPY_CURRENT_TO_HIGH
 BEQ ?CHECK_NO_3

 LDA @BCD_CURRENT_SCORE+3
 STA @BCD_HIGHSCORE+3
?COPY_3
 LDA @BCD_CURRENT_SCORE+2
 STA @BCD_HIGHSCORE+2
?COPY_2
 LDA @BCD_CURRENT_SCORE+1
 STA @BCD_HIGHSCORE+1
?COPY_1
 LDA @BCD_CURRENT_SCORE
 STA @BCD_HIGHSCORE

 ldy #1                  ; es gibt einen neues Highscore
 sty @new_highscore
 ldx #0
 RTS

?CHECK_NO_3
 LDA @BCD_CURRENT_SCORE+2
 CMP @BCD_HIGHSCORE+2
 BMI ?DO_NOT_COPY_CURRENT_TO_HIGH
 BEQ ?CHECK_NO_2
 JMP ?COPY_3

?CHECK_NO_2
 LDA @BCD_CURRENT_SCORE+1
 CMP @BCD_HIGHSCORE+1
 BMI ?DO_NOT_COPY_CURRENT_TO_HIGH
 BEQ ?CHECK_NO_1
 JMP ?COPY_2

?CHECK_NO_1
 LDA @BCD_CURRENT_SCORE
 CMP @BCD_HIGHSCORE
 BMI ?DO_NOT_COPY_CURRENT_TO_HIGH
 JMP ?COPY_1

?DO_NOT_COPY_CURRENT_TO_HIGH
 ldy #0
 ldx #0
 RTS

; setzt den aktuellen Score auf 0 zurueck
; und ab welchem Wert ein neues Leben
@init_score_and_new_live
@init_score_and_new_live_i
  LDY #1
  LDA (@HEAP_PTR),Y ; wert holen
  sta bcd_new_live
  iny
  lda (@heap_ptr),y
  sta bcd_new_live+1

 LDA #0
 STA @BCD_CURRENT_SCORE
 STA @BCD_CURRENT_SCORE+1
 STA @BCD_CURRENT_SCORE+2
 STA @BCD_CURRENT_SCORE+3

 STA bcd_check_score
 STA bcd_check_score+1
 sta bcd_check_score+2

 sta bcd_new_live+2

 sta @new_highscore      ; ist nur 1, wenn es einen neuen Highscore gibt
 RTS

@remember_current_score
  lda @bcd_current_score
  sta @bcd_remember_score
  lda @bcd_current_score+1
  sta @bcd_remember_score+1
  rts

; @return 1, if first two bytes of current_score has changed to remember_score
@has_current_score_changed
  lda @bcd_current_score
  cmp @bcd_remember_score
  bne ?score_has_changed    ; --> bytes unterscheiden sich
  lda @bcd_current_score+1
  cmp @bcd_remember_score+1
  bne ?score_has_changed    ; --> obere bytes unterscheiden sich

  ldy #0
  ldx #0
  rts

?score_has_changed
  ldy #1
  ldx #0
  rts

@bcd_remember_score
 .byte 0,0

BCD_NEW_LIVE
 .byte 0,0,0,0

@BCD_CURRENT_SCORE       ; big endian!
 .byte 0,0,0,0

BCD_CHECK_SCORE
 .byte 0,0,0,0

@new_highscore
 .byte 0

@BCD_HIGHSCORE
 .byte $00,$00,$01,$00

; Kopiert den aktuellen Highscore an die gewuenschte Cursor-Position
; Die Cursor-Position kann mit @fast_gotoxy(x,y) gesetzt werden
; @parameter void
@print_highscore_in_title
 ldy #0
@print_highscore
 jsr ?load_current_cursor_row_and_set_Y_from_colcrs

; lda @BCD_HIGHSCORE+3
; jsr ?print_bcd
 lda @BCD_HIGHSCORE+2
 jsr ?print_bcd
 lda @BCD_HIGHSCORE+1
 jsr ?print_bcd
 lda @BCD_HIGHSCORE
 jmp ?print_bcd

; Initialisiert die internen Register zum setzen der Zahlen an die richtige Position
?load_current_cursor_row_and_set_Y_from_colcrs
 lda @current_cursor_row
 sta @reg
 lda @current_cursor_row+1
 sta @reg+1

 ldy COLCRS
 rts

; Kopiert den aktuellen Score an die gewuenschte Cursor-Position
; Die Cursor-Position kann mit @fast_gotoxy(x,y) gesetzt werden
; @parameter void
@print_score_in_title
 ldy #6
@print_score
 jsr ?load_current_cursor_row_and_set_Y_from_colcrs

; lda @bcd_current_score+3
; jsr ?print_bcd
 lda @bcd_current_score+2
 jsr ?print_bcd
 lda @bcd_current_score+1
 jsr ?print_bcd
 lda @bcd_current_score
 jmp ?print_bcd

; Interne Funktion, um den Akku als 2 BCD-Zahlen in den Screen zu setzen
; (@reg),y zeigt in den Screen
; goody: @score_color wird zur Zahl hinzuge"oder"t damit koennen unterschiedliche
; Farben gesetzt werden.
?print_bcd
 pha
 lsr
 lsr
 lsr
 lsr
 tax
 lda @screen_digit,x
; ora @score_color,y
 sta (@reg),y
 iny
 pla
 and #$0F
 tax
 lda @screen_digit,x
; ora @score_color,y
 sta (@reg),y
 iny
 rts

@screen_digit
 .sbyte '0,'1,'2,'3,'4,'5,'6,'7,'8,'9

;@score_color
; .byte $c0,$c0,$c0,$c0,$c0,$c0,$c0,$c0,$c0,$c0
; .byte $c0,$c0,$c0,$c0,$c0,$c0,$c0,$c0,$c0,$c0
; .byte $c0,$c0,$c0,$c0,$c0,$c0,$c0,$c0,0,0
; .byte 0,0,$40,$40,$40,$40,$40,$40,$40,$40

?hextobcd_in  = @REG+2
?hextobcd_out = @REG+3       ; low byte first

?TABLE_LOW
       .byte    <$01, <$02, <$04, <$08, <$16, <$32, <$64, <$128

;?TABLE_HIGH
;       .byte    >$01, >$02, >$04, >$08, >$16, >$32, >$64, >$128

                ; (Word directive puts low byte first.)

; Print number from 00 to 99 at fast_gotoxy() position
@printSmallDecimalWith0
@printSmallDecimalWith0_I
        ldy #1
        lda (@heap_ptr),y

        jsr @hextobcd_i
        tya
        pha
        jsr ?load_current_cursor_row_and_set_Y_from_colcrs
        pla
        jmp ?print_bcd

@HexToBcd
@HexToBcd_I
        sta ?hextobcd_in

        SED                   ; Output gets added up in decimal.
        LDA #0
        STA ?hextobcd_out     ; Inititalize output word as 0.
        STA ?hextobcd_out+1   ; (NMOS 6502 will need LDA#0, STA ...)

        LDX #7                ; $E is 14 for 2x7 bits.  (0-7 is 8 positions.)
?loop
        ASL ?hextobcd_in      ; Look at next high bit.  If it's 0,
        BCC ?no_add           ; don't add anything to the output for this bit.
        LDA ?hextobcd_out     ; Otherwise get the running output sum
        CLC
        ADC ?TABLE_LOW,X      ; and add the appropriate value for this bit
        STA ?hextobcd_out     ; from the table, and store the new sum.

        LDA ?hextobcd_out+1   ; After low byte, do high byte.
        ADC #0                ; as log as we are <99 this byte will not need
        STA ?hextobcd_out+1

 ?no_add
        DEX                   ; Go down to next bit value to loop again.
        BPL ?loop             ; If still not done, go back for another loop.

        CLD

        ldy ?hextobcd_out
        ldx ?hextobcd_out+1
        RTS

; Show Password
; @printPassword(adr:hashResult)
@printPassword
@printPassword_i
  ldy #1
  lda (@heap_ptr),y
  sta @REG
  iny
  lda (@heap_ptr),y
  sta @REG+1

  ldy #1
  lda (@REG),y
  sta ?password
  iny
  lda (@REG),y
  sta ?password+1
  iny
  lda (@REG),y
  sta ?password+2

  jsr ?load_current_cursor_row_and_set_Y_from_colcrs
  lda ?password
  jsr ?print_password_byte
  lda ?password+1
  jsr ?print_password_byte
  lda ?password+2
  jmp ?print_password_byte

?password
 .byte 0,0,0

?print_password_byte
 pha
 lsr
 lsr
 lsr
 lsr
 tax
 lda @password_digit,x
; ora @score_color,y
 sta (@reg),y
 iny
 pla
 and #$0F
 tax
 lda @password_digit,x
; ora @score_color,y
 sta (@reg),y
 iny
 rts

@password_digit
; .sbyte 'K,'L,'M,'N,'O,'P,'Q,'R,'S,'T,'U,'V,'W,'X,'Y,'Z
 .sbyte 'D,'E,'F,'G,'H,'I,'J,'K,'L,'M,'N,'O,'P,'Q,'R,'S
