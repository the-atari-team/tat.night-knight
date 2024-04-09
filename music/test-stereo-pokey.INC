; Check if stereo pokey is present
; returns 0 if only 1 Pokey is present
; returns 1 if 2 pokeys are present

 .local

; This will stop DLI NMIEN!
@test_stereo   ; returns negative accu, if 2nd POKEY is present
  sei

  lda #0       ; NMI verhindern
	sta NMIEN

; Auf dem 2. Pokey den Counter starten
	lda #$03
	sta SKCTL+16 ; $d21f
	sta AUDF1+16 ; $d210
	ldx #$00
	stx AUDC1+16 ; $d211
	inx
	stx IRQEN+16 ; $d21e

?lp
	ldx VCOUNT
  bne ?lp       ; X-Reg != 0 --> ?lp  ==> warte bis vcount == 0

	stx STIMER+16 ; $d219 starte Pokey-Timer

?loop
	ldx VCOUNT   ; VCOUNT > 127
	bmi ?stereo_pokey_realised

	lda #$01     ; ????
	bit IRQST    ; $d20e
	bne ?loop

  ldy #0       ; Nur ein Pokey vorhanden
  ldx #0

?stop
	lda POKMSK
	sta IRQEN    ; $d20e

	lda #$40     ; NMI wieder zulassen
	sta NMIEN
  cli
  rts


?stereo_pokey_realised
  ldy #1
  jmp ?stop
