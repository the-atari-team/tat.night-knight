; Night-Knight
; cdw by 'The Atari Team' 1990-2022

 .LOCAL

; Move Dude based on @move function, move length Bytes von-adresse, nach-adresse, length
; dabei wird vorwaerts geschoben
; ist optimiert fuer den Dude, 4 Bytes vor den Daten wird geloescht und 4 Bytes hinterher
; .IF .REF @move
@move_dude
@move_dude_iii
; von Adresse
 LDY #1
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+1

; nach Adresse, PM Grafik
 LDY #3
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+2
 SEC
 SBC #4
 STA @REG+4
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+3
 STA @REG+5

; length
 LDY #5
 LDA (@HEAP_PTR),Y ; low Wert holen
 TAX

 LDA #0
 TAY

 STA (@REG+4),Y ; 4 Bytes vor den Daten loeschen
 INY
 STA (@REG+4),Y
 INY
 STA (@REG+4),Y
 INY
 STA (@REG+4),Y

 LDY #0

?DATA_COPY_LOOP
 LDA (@REG),Y        ; 5
 STA (@REG+2),Y      ; 6
 INY                 ; 2
 DEX                 ; 2
 BNE ?DATA_COPY_LOOP ; 3 18 Zyklen pro Byte

 LDA #0

 STA (@REG+2),Y ; 4 Bytes hinterher loeschen
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y
 INY
 STA (@REG+2),Y

 RTS

;// TODO: just for test
;//  colbk:=$0F
;//  @clear_line0_pm0()
;//  colbk:=$18
;//  @clear_line0_pm1()
;//  colbk:=$1f
;//  @clear_line0_pm2()
;//  colbk:=$28
;//  @clear_line0_pm3()
;//  colbk:=$2f
;//  @clear_line1_pm0()
;//  colbk:=$00

;; 11 Bytes ~250 cycles
;@clear_line0_pm0
; lda #255
; ldx #24
;?clear_line0_pm0_loop
; sta $b400+40+32-8,x       ; 5
; dex                       ; 2
; bne ?clear_line0_pm0_loop ; 3 sum: 240
; rts
;
;; 18 Bytes ~264+20 cycles 1 byte
;; 21 Bytes ~228+20 cycles 2 bytes
;; 27 Bytes ~210+20 cycles 4 bytes
;@clear_line0_pm1
; lda #<[$b500+40+32-8]
; ldx #>[$b500+40+32-8]
; sta @REG
; stx @REG+1
;
; lda #255
; ldy #24
;?clear_line0_pm1_loop
; sta (@REG),y              ; 6
; dey                       ; 2
; sta (@REG),y              ; 6
; dey                       ; 2
; bne ?clear_line0_pm1_loop ; 3 sum: 210 228 264
; rts
;
;@clear_line0_pm3
; lda #<[$b700+40+32-8]
; ldx #>[$b700+40+32-8]
; sta @REG
; stx @REG+1
;
; lda #255
; ldy #24
;?clear_line0_pm3_loop
; sta (@REG),y              ; 6
; dey                       ; 2
; bne ?clear_line0_pm3_loop ; 3 sum: 264
; rts
;
;; 27 Bytes ~204+30=234
;; 36 Bytes ~184+40=224
;@clear_line0_pm2
; lda #<[$b600+40+32-8]
; ldx #>[$b600+40+32-8]
; sta @REG
; stx @REG+1
; clc
; adc #8
; sta @REG+2
; stx @REG+3
; clc
; adc #8
; sta @REG+4
; stx @REG+5
;
; lda #255
; ldy #8
;?clear_line0_pm2_loop
; sta (@REG),y              ; 6
; sta (@REG+2),y            ; 6
; sta (@REG+4),y            ; 6
; dey                       ; 2
; bne ?clear_line0_pm2_loop ; 3 sum: 184 (8 * 23)
; rts
;
;; 20 Bytes ~160 cycles
;@clear_line1_pm0
; lda #255
; ldx #6
;?clear_line1_pm0_loop
; sta $b400+64+32-8,x       ; 5
; sta $b400+64+32-8+6,x     ; 5
; sta $b400+64+32-8+12,x    ; 5
; sta $b400+64+32-8+18,x    ; 5
; dex                       ; 2
; bne ?clear_line1_pm0_loop ; 3 sum: 150 ~38% faster
; rts
;
