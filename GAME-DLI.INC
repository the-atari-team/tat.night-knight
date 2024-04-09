; -*- text -*-
;
; Editor Display List Interrupts
;
; THIS FILE WILL INCLUDE BY OTHER FILE
;
 .local

; Den Displaylist Interrupt lassen wir im VBI setzen, so
; laufen wir nicht Gefahr damit etwas kaputt zu machen

; SHOW_COLOR_COURSE=1
;pal=$D014

?DEBUG_COLOR_0=$00
?DEBUG_COLOR_1=$32
?DEBUG_COLOR_2=$52
?DEBUG_COLOR_3=$72
?DEBUG_COLOR_4=$12

COLOR_HEADLINE_PAL .byte $16,$14,$12
COLOR_HEADLINE_NTSC .byte $26,$24,$22

@INIT_NMI_AND_DLI
     jsr @stop_displaylist_interrupts

     ldx #0 ; Index to Color_Headline_pal

     lda pal
     cmp #1
     beq ?system_is_pal

     lda #$10
     sta ?pal_ntsc_color_add_vbi+1

     ldx #3 ; Index to Color_Headline_pal + 3

?system_is_pal
     lda COLOR_HEADLINE_PAL,x
     sta ?set_headline_color_1+1
     lda COLOR_HEADLINE_PAL+1,x
     sta ?set_headline_color_2+1
     lda COLOR_HEADLINE_PAL+2,x
     sta ?set_headline_color_3+1

     LDA #6         ; Nutze Immediate(6) VBI
     LDY #<?GAME_VBI
     LDX #>?GAME_VBI
     JMP SETVBV


@stop_displaylist_interrupts
    lda #$40
;    sta ?nmien_value
    sta nmien
    rts


@start_displaylist_interrupts
    lda #$c0
;    sta ?nmien_value
    sta nmien
    rts

; ?nmien_value
; .byte 0

;
; OO   OO OOOOO  OOOO
; OO   OO OO  OO  OO
; OO   OO OO  OO  OO
; OO   OO OOOOO   OO
; OO   OO OO  OO  OO
;  OO OO  OO  OO  OO
;   OOO   OOOOO  OOOO
;

?GAME_VBI
     LDA #0
     STA 77 ; no colorswitch

;     LDA #$0
;     STA NMIEN ; Displaylist Interrupt sperren

     jsr @reset_meter

     lda @show_screen             ; with show_screen we can switch between the 3 Screen Types
     cmp #MESSAGE_SCREEN          ; show message in the middle
     beq ?show_message_screen

     cmp #INTRO_SCREEN            ; Title Screen
     beq ?show_intro_screen

     cmp #OUTRO_SCREEN
     beq ?show_outro_screen

; Show Game Screen
     LDY #<@GAME_DLIST            ; Game Screen
     LDX #>@GAME_DLIST

     LDA #<?GAME_DLI_NIGHT_KNIGHT
     STA VDSLST
     LDA #>?GAME_DLI_NIGHT_KNIGHT
     STA VDSLST+1

     lda #30
     sta ?message_countdown

     jmp ?More_interrupt

; Show Screen with a text element
?show_message_screen
     LDY #<@GAME_MESSAGE_DLIST      ; like Game Screen, with GR0 Line in the middle
     LDX #>@GAME_MESSAGE_DLIST

     LDA #<?GAME_DLI_NIGHT_KNIGHT
     STA VDSLST
     LDA #>?GAME_DLI_NIGHT_KNIGHT
     STA VDSLST+1
;     LDA #<?SHOW_MESSAGE_NIGHT_DLI
;     STA VDSLST
;     LDA #>?SHOW_MESSAGE_NIGHT_DLI
;     STA VDSLST+1

     lda #9
     sta ?message_countdown

     jmp ?More_interrupt

?show_intro_screen
     LDY #<@INTRO_DLIST        ; Shows the Night Knight Title
     LDX #>@INTRO_DLIST

     LDA #<?INTRO_DLI
     STA VDSLST
     LDA #>?INTRO_DLI
     STA VDSLST+1
     jmp ?More_interrupt


?show_outro_screen
     LDY #<@OUTRO_DLIST       ; Shows the outro
     LDX #>@OUTRO_DLIST

     LDA #<?OUTRO_DLI
     STA VDSLST
     LDA #>?OUTRO_DLI
     STA VDSLST+1

; no jmp need!
;      jmp ?More_interrupt

?More_interrupt
     STY SDLSTL
     STX SDLSTL+1

;     LDA ?nmien_value
;     STA NMIEN ; Displaylist Interrupt ermoeglichen

; flash!

     ldy @colbk_flash
     beq ?no_colbk_change

;     ldy @colbk_flash
     lda ?colbk_colors,y
     clc
?pal_ntsc_color_add_vbi
     adc #0
     sta 712
     sta colbk
     dec @colbk_flash

?no_colbk_change

     ldy @player4_flash
     beq ?no_player4_change

     lda ?player4_colors,y
     sta @block_c4+4  ;     sta 711
     sta @block_c4+5  ;     sta COLPF3
     dec @player4_flash

?no_player4_change

    JMP SYSVBV

?title_font=$c8

; Um einen Flash auszuloesen, einfach @colbk_flash:=15 setzen
; for yellow flash
?colbk_colors
    .byte $00,$00,$10,$10,$11,$12,$13,$14,$15,$16,$17,$18,$1A,$1C,$1E,$1E

?player4_colors
    .byte $32,$34,$36,$38,$3a,$3c,$3f

; every DLI we increment this number, in VBI we set it to 0

?GAME_DLI_NIGHT_KNIGHT
 pha

; 0 2 4 6 8 a c e
?set_headline_color_1
 lda #0   ; muss zuerst gesetzt werden wg. Zeitproblem im DLI
 sta colpf2

?set_headline_color_2
 lda #0
 sta colpf1

?set_headline_color_3
 lda #0     ; Color Night Knight Headline
 sta colpf0

 LDA #<?GAME_DLI_2 ; switch to other DLI
 STA VDSLST
 LDA #>?GAME_DLI_2
 STA VDSLST+1
 pla
 rti

?GAME_DLI_2
 pha
 jsr @multi_sprite_dli_sub

 LDA #<?GAME_DLI_3 ; switch to other DLI
 STA VDSLST
 LDA #>?GAME_DLI_3
 STA VDSLST+1
 pla
 rti

?GAME_DLI_3
 pha
 jsr @multi_sprite_dli_sub

 LDA #<?GAME_DLI_STATUS_GR0 ; switch to other DLI
 STA VDSLST
 LDA #>?GAME_DLI_STATUS_GR0
 STA VDSLST+1
 pla
 rti


?GAME_DLI_STATUS_GR0
 PHA
 CLD
; lda #?DEBUG_COLOR_1
; sta colbk

 lda #?title_font     ; Stage font Graphics 0
 sta chbase

 lda 708
 sta COLPF0
 lda #12
 sta COLPF1   ; 709
 lda #0
 sta COLPF2   ; 710

; lda #17      ; Missiles einzeln betrachten
; sta PRIOR

 ; Missiles for heart and seconds

; lda 711       ; #$32
; sta COLPF3
; sta COLPM0   ; Farbe Missiles
; sta COLPM1

 clc
 lda #x_pos_heart      ; XPosition Herz
 sta HPOSM1
 adc #2
 sta HPOSM0

; lda #$30
; sta COLPM2

 lda #~00110000 ; full 4 color clocks width
 sta SIZEM

 lda #X_POS_SCORE ; 124     ; Hintergrund fuer Zeit, falls diese ablaeuft
 asl
 asl
 clc
 adc #xoffset
 sta HPOSM2

; lda #$38
; sta colbk
; sta w-sync
;
; lda 712     ; restore old background color
; sta colbk

; um den Dude ueberspringen zu lassen, hier die erste
; Line setzen

; lda #$ff
; sta COLPF2   ; 710
 jsr @multi_sprite_dli_sub
; lda #0
; sta COLPF2   ; 710

 LDA #<?NIGHT_DLI_Stage_line
 STA VDSLST
 LDA #>?NIGHT_DLI_Stage_line
 STA VDSLST+1

; lda 712
; sta colbk

 pla
 rti

?dli_number_for_color
 .byte 0

?game_font=$cc

?NIGHT_DLI_Stage_line
 pha

 lda 709
 sta wsync       ; we need this or we see a color switch
 sta COLPF1
 lda 710
 sta COLPF2      ; 710

 lda #?game_font
 sta chbase

 jsr @multi_sprite_dli_sub

 LDA #<?GAME_DLI_multi_sprites
 STA VDSLST
 LDA #>?GAME_DLI_multi_sprites
 STA VDSLST+1

 PLA
 RTI

?GAME_DLI_multi_sprites
  pha
  jsr @multi_sprite_dli_sub
  pla

  dec ?message_countdown
  beq ?MESSAGE_NIGHT_DLI

  rti

;
; OOOOOO                  OO          OO   OO                                                  OOOOO  OO     OOOO
;   OO                    OO          OOO OOO                                                  OO  OO OO      OO
;   OO    OOOO  OO   OO OOOOOO        OOOOOOO  OOOO   OOOO   OOOO   OOOOO  OOOOO  OOOO         OO  OO OO      OO
;   OO   OO  OO  OO OO    OO   OOOOOO OO O OO OO  OO OO     OO     OO  OO OO  OO OO  OO OOOOOO OO  OO OO      OO
;   OO   OOOOOO   OOO     OO          OO   OO OOOOOO  OOOO   OOOO  OO  OO OO  OO OOOOOO        OO  OO OO      OO
;   OO   OO      OO OO    OO          OO   OO OO         OO     OO OO  OO  OOOOO OO            OO  OO OO      OO
;   OO    OOOO  OO   OO    OOO        OO   OO  OOOO   OOOO   OOOO   OOOOO     OO  OOOO         OOOOO  OOOOOO OOOO
;                                                                         OOOOO


?MESSAGE_NIGHT_DLI
 pha

; lda #?DEBUG_COLOR_1
; sta colbk

 lda #0
 sta COLPF2   ; 710
 lda #12
 sta COLPF1   ; 709
 lda #?title_font
 sta chbase

 sta wsync
 sta wsync
 sta wsync
 sta wsync
 sta wsync
 sta wsync
 jsr @multi_sprite_dli_sub
 sta wsync
 sta wsync
 sta wsync

 lda #?game_font
 sta chbase
 lda 709
 sta COLPF1   ; 709
 lda 710
 sta wsync
 sta COLPF2   ; 710
 sta wsync
 sta wsync

; IMPORTANT WSYNC, or we earn a wrong black line, seeable in message-line
 sta wsync

 jsr @multi_sprite_dli_sub
; lda #?DEBUG_COLOR_0
; sta colbk

 pla
 rti

?message_countdown
  .byte 0



;
; OOOOOO  OO    OO   OOO                OOOOO  OO     OOOO
;   OO          OO    OO                OO  OO OO      OO
;   OO   OOO  OOOOOO  OO   OOOO         OO  OO OO      OO
;   OO    OO    OO    OO  OO  OO OOOOOO OO  OO OO      OO
;   OO    OO    OO    OO  OOOOOO        OO  OO OO      OO
;   OO    OO    OO    OO  OO            OO  OO OO      OO
;   OO   OOOO    OOO OOOO  OOOO         OOOOO  OOOOOO OOOO
;

?INTRO_DLI
 pha
 jsr ?gr0_line

 LDA #<?INTRO_DLI_line2
 STA VDSLST
 LDA #>?INTRO_DLI_line2
 STA VDSLST+1

 pla
 rti

?INTRO_DLI_line2
 pha
 jsr ?gr0_line

 LDA #<?INTRO_DLI_gr7
 STA VDSLST
 LDA #>?INTRO_DLI_gr7
 STA VDSLST+1

 pla
 rti

?INTRO_DLI_gr7
 pha

; lda #?DEBUG_COLOR_3
; sta colbk

; lda #?game_font
 sta wsync
; sta chbase

; 0 2 4 6 8 a c e
HEADLINE_INTRO=$f0

; lda #HEADLINE_INTRO|$0a    ; Color Night Knight Headline
 lda @headline_color+0
 sta COLPF0
; lda #HEADLINE_INTRO|$0c
 lda @headline_color+1
 sta COLPF1
; lda #HEADLINE_INTRO|$0e
 lda @headline_color+2
 sta COLPF2

 LDA #<?DLI_for_GR0
 STA VDSLST
 LDA #>?DLI_for_GR0
 STA VDSLST+1

; lda #?DEBUG_COLOR_0
; sta colbk

 pla
 rti

?gr0_line
; lda #?DEBUG_COLOR_1
; sta colbk

 lda #?title_font
 sta chbase

 lda #0
 sta COLPF2   ; 710
 lda #14
 sta COLPF1   ; 709

 sta wsync
 sta wsync
 sta wsync
 sta wsync
 lda #10
 sta wsync
 sta COLPF1   ; 709

; lda #?DEBUG_COLOR_0
; sta colbk
 rts


?DLI_for_GR0
 pha

 lda #$3E
; lda sdmctl THIS IS VERY DANGEROUS!!!
 sta dmactl

 jsr ?gr0_line

 pla
 rti


;
;  OOOO                  OO   OOO                OOOOO  OO     OOOO
; OO  OO                 OO    OO                OO  OO OO      OO
; OO      OOOOO  OOOO  OOOOOO  OO   OOOO         OO  OO OO      OO
; OO     OO  OO OO       OO    OO  OO  OO OOOOOO OO  OO OO      OO
; OO     OO  OO  OOOO    OO    OO  OOOOOO        OO  OO OO      OO
; OO  OO OO  OO     OO   OO    OO  OO            OO  OO OO      OO
;  OOOO   OOOOO  OOOO     OOO OOOO  OOOO         OOOOO  OOOOOO OOOO
;


?OUTRO_DLI
 pha
 jsr ?gr0_line

 LDA #<?OUTRO_DLI_gr13
 STA VDSLST
 LDA #>?OUTRO_DLI_gr13
 STA VDSLST+1

 pla
 rti

?outro_font=$c0
?OUTRO_DLI_gr13
 pha

; lda #?DEBUG_COLOR_2
; sta colbk

 lda #$3d                    ; we want 32 instead of 40 bytes per line
 sta dmactl

 lda #?outro_font
 sta wsync
 sta chbase

; 0 2 4 6 8 a c e

; lda #HEADLINE_INTRO|$0a    ; Color Night Knight Headline
 lda @headline_color+0
 sta COLPF0
; lda #HEADLINE_INTRO|$0c
 lda @headline_color+1
 sta COLPF1
; lda #HEADLINE_INTRO|$0e
 lda @headline_color+2
 sta COLPF2
; inverse Zeichen!!!
 lda @headline_color+3
 sta COLPF3

 LDA #<?DLI_for_GR0
 STA VDSLST
 LDA #>?DLI_for_GR0
 STA VDSLST+1

; lda #?DEBUG_COLOR_0
; sta colbk

 pla
 rti

