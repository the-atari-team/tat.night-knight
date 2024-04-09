; -*- text -*-
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;

    .LOCAL

; 50Hz oder 60 Hz
; call @Test_frequence()
; @return 50 bei PAL, 60 bei NTSC

@TEST_FREQUENCE
    lda VCOUNT     ; we must make sure, we are NOT 0!
    bne ?loop12

    sta wsync
    sta wsync      ; vcount >= 1

?loop1
		lda VCOUNT
		beq ?loop2     ; vcount==0, check last value

?loop12
		tay            ; remember last value in Y-reg
		jmp ?loop1

?loop2
		cpy #155       ; check last value from Y-Reg
		bmi ?less_155

		; hier ist PAL
		ldy #50
		ldx #0
		rts

?less_155
		; hier ist NTSC
		ldy #60
		ldx #0
		rts
