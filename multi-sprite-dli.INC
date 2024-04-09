meter=$80   ; yposition div 8 der Sprite position

regA=$81
regX=$82

data = $83 ; 2 bytes

spr_flag    = $85
nr_sprite   = $86
block_y     = $87
block_dy    = $88
last_sprite = $89

; Multi sprite interrupt, must be called every 8 screen lines (in gr.0 or gr.12 every Displaylist line!)
@multi_sprite_dli_sub
;			sta regA
			stx regX

; Just for tests
;  lda #8
;  sta colbk

			ldx meter           ; yposition div 8

      lda @block_c4,x
      sta colpf3          ; Farbe player 4 (Missiles oder Inverse Chararcter)

			lda block_x0,x			;player 0
			beq ?no_sprite0

			sta hposp0

			lda block_c0,x
			sta colpm0

?no_sprite0
			lda block_x1,x			;player 1
			beq ?no_sprite1

			sta hposp1

			lda block_c1,x
			sta colpm1

?no_sprite1
			lda block_x2,x			;player 2
			beq ?no_sprite2

			sta hposp2

			lda block_c2,x
			sta colpm2

?no_sprite2
			lda block_x3,x			;player 3
			beq ?no_sprite3

			sta hposp3

			lda block_c3,x
			sta colpm3

?no_sprite3

			lda #0				;loeschen Sie den Artikel
			sta block_x0,x
			sta block_x1,x
			sta block_x2,x
			sta block_x3,x
			sta block_status,x

			inc meter

?dli_end
;  lda #0
;  sta colbk

	ldx regX
;	lda regA
  rts


; reset the meter value, must be called in NMI!
@reset_meter
  lda #3
  sta meter
  rts

; fuer jeden DLI werden diese 10 Bytes gebraucht

  .align 32
block_status .dc 32 0    ; Hilfstafel zur Bestimmung der Besetzung von Sprites
block_x0     .dc 32 0    ; Sprite-Positionen 0
block_x1     .dc 32 0    ; Sprite-Positionen 1
block_x2     .dc 32 0    ; Sprite-Positionen 2
block_x3     .dc 32 0    ; Sprite-Positionen 3

block_c0     .dc 32 0    ; Spritefarbe 0
block_c1     .dc 32 0
block_c2     .dc 32 0
block_c3     .dc 32 0
@block_c4    .dc 32 0    ; Spritefarbe 5
