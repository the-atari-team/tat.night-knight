;
;
;
; assembler optimized copy functions for elevator
;
 .local

screen_line_plus_xpos
 CLC
 LDA ELV_SCREEN_LINE
 ADC ELV_XPOS
 tay
 LDA ELV_SCREEN_LINE+1
 ADC #0
 tax
 rts

screen_plus_xadd_second
 clc
 LDA ELV_SCREEN ; (6)
 adc ELV_XADD_SECOND
 tay
 LDA ELV_SCREEN+1 ; (13)
 adc ELV_XADD_SECOND+1
 tax
 rts

background1
 .byte 0,0,0,0,0,0

background2
 .byte 0,0,0,0,0,0

@STORE_LR
; @STORE_LR
;
; [199]  screen := screen_line + xpos
;
 jsr screen_line_plus_xpos
 sty ELV_SCREEN
 stx ELV_SCREEN+1
 sty @reg
 stx @reg+1
;
; [200]  @move(screen, adr:background1, 4)
;

 ldy #0
 lda (@reg),y
 sta background1
 iny
 lda (@reg),y
 sta background1+1
 iny
 lda (@reg),y
 sta background1+2
 iny
 lda (@reg),y
 sta background1+3

 jsr screen_plus_xadd_second
 sty @reg
 stx @reg+1

 ldy #0
 lda (@reg),y
 sta background2
 iny
 lda (@reg),y
 sta background2+1
 iny
 lda (@reg),y
 sta background2+2
 iny
 lda (@reg),y
 sta background2+3
 RTS


;
; [233]  procedure @restore_lr()
;
@RESTORE_LR
; @RESTORE_LR

 jsr screen_line_plus_xpos
 sty ELV_SCREEN
 stx ELV_SCREEN+1
 sty @reg
 stx @reg+1

 ldy #0
 lda background1
 sta (@reg),y
 iny
 lda background1+1
 sta (@reg),y
 iny
 lda background1+2
 sta (@reg),y
 iny
 lda background1+3
 sta (@reg),y

 jsr screen_plus_xadd_second
 sty @reg
 stx @reg+1

 ldy #0
 lda background2
 sta (@reg),y
 iny
 lda background2+1
 sta (@reg),y
 iny
 lda background2+2
 sta (@reg),y
 iny
 lda background2+3
 sta (@reg),y
 rts

;screen_line_plus_ypos
; CLC
; LDA ELV_SCREEN_LINE
; ADC ELV_XPOS
;; ldx elv_ypos
;; ADC ELV_mul40_low,x
; tay
; LDA ELV_SCREEN_LINE+1
;; ADC ELV_mul40_high,x
; adc #0
; tax
; rts

;screen_plus_yadd_second
; clc
; LDA ELV_SCREEN ; (6)
; adc ELV_YADD_SECOND
; tay
; LDA ELV_SCREEN+1 ; (13)
; adc ELV_YADD_SECOND+1
; tax
; rts


@STORE_UD
; @STORE_UD
;
; [199]  screen := screen_line + xpos
;
 jsr screen_line_plus_xpos
 sty ELV_SCREEN
 stx ELV_SCREEN+1
 sty @reg
 stx @reg+1
;
; [200]  @move(screen, adr:background1, 4)
;

 ldy #0
 lda (@reg),y
 sta background1
 iny
 lda (@reg),y
 sta background1+1
 iny
 lda (@reg),y
 sta background1+2

 ldy #40

 lda (@reg),y
 sta background1+3
 iny
 lda (@reg),y
 sta background1+4
 iny
 lda (@reg),y
 sta background1+5

 jsr screen_plus_xadd_second
 sty @reg
 stx @reg+1

 ldy #0
 lda (@reg),y
 sta background2
 iny
 lda (@reg),y
 sta background2+1
 iny
 lda (@reg),y
 sta background2+2

 ldy #40

 lda (@reg),y
 sta background2+3
 iny
 lda (@reg),y
 sta background2+4
 iny
 lda (@reg),y
 sta background2+5
 RTS


;
; [233]  procedure @restore_lr()
;
@RESTORE_UD
; @RESTORE_UD

 jsr screen_line_plus_xpos
 sty ELV_SCREEN
 stx ELV_SCREEN+1
 sty @reg
 stx @reg+1

 ldy #0
 lda background1
 sta (@reg),y
 iny
 lda background1+1
 sta (@reg),y
 iny
 lda background1+2
 sta (@reg),y

 ldy #40
 lda background1+3
 sta (@reg),y
 iny
 lda background1+4
 sta (@reg),y
 iny
 lda background1+5
 sta (@reg),y

 jsr screen_plus_xadd_second
 sty @reg
 stx @reg+1

 ldy #0
 lda background2
 sta (@reg),y
 iny
 lda background2+1
 sta (@reg),y
 iny
 lda background2+2
 sta (@reg),y

 ldy #40
 lda background2+3
 sta (@reg),y
 iny
 lda background2+4
 sta (@reg),y
 iny
 lda background2+5
 sta (@reg),y
 rts
