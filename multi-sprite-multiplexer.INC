; -*- text -*-
; Multisprite Multiplexer
;cdw by 'The Atari Team' 2022
;
; Geschrieben fuer Night Knight
;
; based on Shanti77 & tebe code, thanks for that code!

; Der Atari hat 4 Player, die aber den ganzen Schirm von der Hoehe her einnehmen.
; Dieser Code hilft dabei bis zu MAX_SPRITES (bis zu 16) SPRITES darzustellen
; Dabei wird jede 8. Bildschirmzeile ein DLI gebraucht, diese muessen an den Richtigen
; Positionen liegen.
; Dann kann man locker 16 Sprites (8bit breit, 16 Zeilen hoch) darstellen
; Wenn man Flackern akzeptiert, dann auch alle nebeneinander.
; Man sollte es aber auf max 8 Sprites beschraenken.
; Auf den alten Ataris nebst Roehrenmonitor mit einer leicht nachlaufenden Plasma-Schicht faellt das
; Flackern nicht so stark auf. Im Altirra kann man Frame blending in den Video Einstellungen einschalten.
; Auf aktuellen LED/LCD Displays flackert es etwas staerker.
;
; Es muss ein
; word array @all_sprite_data_table[1] = [...]
; angelegt werden, das fuer jeden darzustellenden Sprite einen Eintrag hat.
; Der Wert von @sprite_shape[i] zeigt dann in diese Tabelle und stellt den Sprite da.
; Welcher Player fuer die Darstellung verwendet wird ist nicht fix und variiert stark.
; Deshalb muss man die Kollisionserkennung selbst erstellen.
;
; Der Code ist etwas laenglich, deshalb aber recht flott, da unroll-loop angewendet wird.
; Gerade beim Schreiben der Daten wird auf Schleifen-Konstrukte verzichtet.
;
; Wie viele Sprites auf NTSC Systemen dargestellt werden koennen muessen spaetere Tests zeigen

pmadr=$1000

@sprite_x
 .DC MAX_SPRITES 0

; sprite_x        *= *+MAX_SPRITES    ;die X-Position des Objekts
;sprite_dx       *= *+MAX_SPRITES    ;X-Position nach dem Komma
@sprite_y
 .DC MAX_SPRITES 0
; sprite_y        *= *+MAX_SPRITES
;sprite_dy       *= *+MAX_SPRITES

@sprite_shape
 .DC MAX_SPRITES 0

; sprite_shape    *= *+MAX_SPRITES    ;die Form des Objekts
@sprite_color
 .DC MAX_SPRITES 0
; sprite_color    *= *+MAX_SPRITES    ;color 0 objekt

;sprite_anim     *= *+MAX_SPRITES    ;die Anzahl der Frames fuer die Animation des Objekts
;sprite_anim_speed *= *+MAX_SPRITES    ;Objektanimationsgeschwindigkeit
;sprite_anim_waitfor *=*+MAX_SPRITES ; wie lange noch auf Animationssprung warten

 .local

; Sprite initialisierung
@init_sprites
    lda #MAX_SPRITES-1
    sta last_sprite

init_sprite2
    lda #0
    tax
?loop2
    sta pmadr+$300,x        ; loesche saemtliche Player/Missiles
    sta pmadr+$400,x
    sta pmadr+$500,x
    sta pmadr+$600,x
    sta pmadr+$700,x
    dex
    bne ?loop2

    rts

;
;     OO                                                    OO    OO
;     OO                                                          OO
;  OOOOO OOOOO   OOOOO OO   OO         OOOO  OOOOO  OOOOO  OOO  OOOOOO  OOOO   OOOO
; OO  OO OO  OO OO  OO OO   OO OOOOOO OO     OO  OO OO  OO  OO    OO   OO  OO OO
; OO  OO OO     OO  OO OO O OO         OOOO  OO  OO OO      OO    OO   OOOOOO  OOOO
; OO  OO OO     OO  OO OO O OO            OO OOOOO  OO      OO    OO   OO         OO
;  OOOOO OO      OOOOO  OO OO          OOOO  OO     OO     OOOO    OOO  OOOO   OOOO
;                                            OO

; Zeichnet immer alle Sprites,
; darf erst ab VCOUNT==105 starten, sonst flackert es stark und es kommt zu Darstellungsfehlern
@show_sprites
; lda #$34
; sta colbk
; sta 712

    ldy #0
    sty spr_flag

    lda @sprite_x           ; Es werden nur Sprites angezeigt, die eine X-Position != 0 haben
    beq ?no_spieler

    jsr ?print_sprite        ; Spieler Sprite 0, flackert niemals!
                             ; TIPP: Die hellste Farbe nehmen! Je dunkler desto weniger ist flackern warnehmbar
?no_spieler
    ldy last_sprite

?loop3
    lda @sprite_x,y
    beq ?no_print_sprite

    jsr ?print_sprite     ; Y enthaelt SpriteNummer, Akku die X-Position

?no_print_sprite
    dey
    bne ?there_are_more_sprites
    ldy #MAX_SPRITES-1

?there_are_more_sprites
    cpy last_sprite
    bne ?loop3


    lda spr_flag
    beq ?no_start
    sta last_sprite

?no_start
;    lda block_x01+1        ;player 0 und 1
;    sta hposp1
;    sta hposp0
;    lda block_c0+1
;    sta colpm0
;    lda block_c1+1
;    sta colpm1
;    lda block_x23+1        ;player 2 und 3
;    sta hposp3
;    sta hposp2
;    lda block_c2+1
;    sta colpm2
;    lda block_c3+1
;    sta colpm3
;
;    lda #0
;    sta block_x01+1
;    sta block_x23+1
;    sta block_status+1
;;    sta block_status+28

;    lda #0
;    sta colbk
;    sta 712
    rts







; Zeichne einen Sprite aktuelle Nummer [0 bis MAX_SPRITE] in Y
?print_sprite
;    lda #$32
;    sta colbk

    lda @sprite_y,y    ; bereits gelesen

;    cmp #POSY_MIN     ; Kontrolle der Position, code ist unnoetig, sollte hier nicht gemacht werden
;    bcc quit
;    cmp #POSY_MAX
;    bcs quit

; Wir haben Blockzeilen (jeweils 8 echte Zeilen hoch) hier drin bewegt sich ein Sprite
    sta block_y
    lsr
    lsr
    lsr
    tax               ; erste Blocknummer

    lda block_y
    and #~00000111
    sta block_dy       ; Zeile innerhalb eines Blockes

    bne ?no_dex
    dex                ; wenn dy = 0, dann verringern Sie die Nummer des ersten Blocks
?no_dex

    lda block_status,x
    ora block_status+1,x
    ora block_status+2,x
    lsr
    bcc ?print_sprite_0
    lsr
    bcc ?print_sprite_1
    lsr
    bcc ?print_sprite_2
    lsr
    bcc ?print_sprite_3

; Es ist unmoeglich, einen Sprite zu zeichnen
    lda spr_flag
    bne ?quit
    sty spr_flag
?quit
    rts

; Y-Register enthaelt Spritenummer [0 bis MAX_SPRITES]
; X-Register enthaelt aktuelle Y-Position auf dem Screen (*8 fuer echte Hoehe)
?print_sprite_0
    inc block_status,x
    inc block_status+2,x

; Festlegen der Position und Farbe von Sprites im Block
    lda block_x0+3,x
    bne ?no_inc
    inc block_x0+3,x
?no_inc
    lda @sprite_x,y        ; sprite 0
    sta block_x0,x

    lda @sprite_color,y
    sta block_c0,x

    ldx @sprite_shape,y    ; in X steht jetzt der Inhalt
    jmp ?shape_0

?print_sprite_1
    lda #2
    ora block_status,x    ; Beanspruchen Sie das ausgewaehlte Sprite im Status
    sta block_status,x
    lda #2
    ora block_status+2,x
    sta block_status+2,x


    lda block_x1+3,x
    bne ?no_inc2
    inc block_x1+3,x
?no_inc2
    lda @sprite_x,y        ; sprite 1
    sta block_x1,x

    lda @sprite_color,y
    sta block_c1,x

    ldx @sprite_shape,y
    jmp ?shape_1

?print_sprite_2
    lda #4
    ora block_status,x    ;Beanspruchen Sie das ausgewaehlte Sprite im Status
    sta block_status,x
    lda #4
    ora block_status+2,x
    sta block_status+2,x


    lda block_x2+3,x
    bne ?no_inc3
    inc block_x2+3,x
?no_inc3
    lda @sprite_x,y        ; sprite 2
    sta block_x2,x

    lda @sprite_color,y
    sta block_c2,x

    ldx @sprite_shape,y
    jmp ?shape_2

?print_sprite_3
    lda #8
    ora block_status,x    ;Beanspruchen Sie das ausgewaehlte Sprite im Status
    sta block_status,x
    lda #8
    ora block_status+2,x
    sta block_status+2,x


    lda block_x3+3,x
    bne ?no_inc4
    inc block_x3+3,x
?no_inc4
    lda @sprite_x,y        ; sprite 3
    sta block_x3,x

    lda @sprite_color,y
    sta block_c3,x

    ldx @sprite_shape,y
    jmp ?shape_3



?shape_0
    lda @all_sprite_data_table_low,x
    sta data
    lda @all_sprite_data_table_high,x
    sta data+1

    sty nr_sprite
    ldx block_y                   ; Y-Position im Screen

?set_sprite_0
    jsr player0a                  ; zeichne den Sprite

    ldy block_dy
    lda tab_clear_sprite_0_low,y
    sta ?clear_sprite_0+1
    lda tab_clear_sprite_0_high,y
    sta ?clear_sprite_0+2
    ldy nr_sprite

;    lda #$81 ; mit diesem Byte ist sehr gut zu sehen, wie die Player angewendet werden.
    ldx block_y                   ; Y-Position im Screen
    lda #0
?clear_sprite_0
    jmp cls0                     ; Ansprung der clear Routine

?shape_1
    lda @all_sprite_data_table_low,x
    sta data
    lda @all_sprite_data_table_high,x
    sta data+1

    sty nr_sprite
    ldx block_y

?set_sprite_1
    jsr player1a

    ldy block_dy
    lda tab_clear_sprite_1_low,y
    sta ?clear_sprite_1+1
    lda tab_clear_sprite_1_high,y
    sta ?clear_sprite_1+2

    ldy nr_sprite
    ldx block_y                   ; Y-Position im Screen
    lda #0

?clear_sprite_1
    jmp cls0b


?shape_2
    lda @all_sprite_data_table_low,x
    sta data
    lda @all_sprite_data_table_high,x
    sta data+1

    sty nr_sprite
    ldx block_y
?set_sprite_2
    jsr player2a

    ldy block_dy
    lda tab_clear_sprite_2_low,y
    sta ?clear_sprite_2+1
    lda tab_clear_sprite_2_high,y
    sta ?clear_sprite_2+2

    ldy nr_sprite
    ldx block_y                   ; Y-Position im Screen
    lda #0
?clear_sprite_2
    jmp cls0c



?shape_3
    lda @all_sprite_data_table_low,x
    sta data
    lda @all_sprite_data_table_high,x
    sta data+1

    sty nr_sprite
    ldx block_y
?set_sprite_3
    jsr player3a

    ldy block_dy
    lda tab_clear_sprite_3_low,y
    sta ?clear_sprite_3+1
    lda tab_clear_sprite_3_high,y
    sta ?clear_sprite_3+2

    ldy nr_sprite
    ldx block_y
    lda #0
?clear_sprite_3
    jmp cls0d


; Form-Arrays    max=128


tab_clear_sprite_0_low    .byte <cls0,<cls1,<cls2,<cls3,<cls4,<cls5,<cls6,<cls7
tab_clear_sprite_0_high    .byte >cls0,>cls1,>cls2,>cls3,>cls4,>cls5,>cls6,>cls7


cls0
    sta pmadr+$400+$10,x

    sta pmadr+$400-8,x
    sta pmadr+$400-7,x
    sta pmadr+$400-6,x
    sta pmadr+$400-5,x
    sta pmadr+$400-4,x
    sta pmadr+$400-3,x
    sta pmadr+$400-2,x
    sta pmadr+$400-1,x


    rts

cls1
    sta pmadr+$400+$13,x
    sta pmadr+$400+$14,x
    sta pmadr+$400+$15,x
    sta pmadr+$400+$16,x
    sta pmadr+$400+$17,x
    sta pmadr+$400+$18,x
    jmp cls7_36


cls2
    sta pmadr+$400+$13,x
    sta pmadr+$400+$14,x
    sta pmadr+$400+$15,x
    sta pmadr+$400+$16,x
    sta pmadr+$400+$17,x
    jmp cls7_30

cls3
    sta pmadr+$400+$13,x
    sta pmadr+$400+$14,x
    sta pmadr+$400+$15,x
    sta pmadr+$400+$16,x
    jmp cls7_24

cls4
    sta pmadr+$400+$13,x
    sta pmadr+$400+$14,x
    sta pmadr+$400+$15,x
    jmp cls7_18


cls5
;    cpx #POSY_MAX-32
;    bcs cls7_12
    sta pmadr+$400+$13,x
    sta pmadr+$400+$14,x
    jmp cls7_12

cls6
    sta pmadr+$400+$13,x
    jmp cls7_6


cls7
    sta pmadr+$400-7,x
cls7_6
    sta pmadr+$400-6,x
cls7_12
    sta pmadr+$400-5,x
cls7_18
    sta pmadr+$400-4,x
cls7_24
    sta pmadr+$400-3,x
cls7_30
    sta pmadr+$400-2,x
cls7_36
    sta pmadr+$400-1,x

    sta pmadr+$400+$10,x
    sta pmadr+$400+$11,x
    sta pmadr+$400+$12,x
    rts


tab_clear_sprite_1_low    .byte <cls0b,<cls1b,<cls2b,<cls3b,<cls4b,<cls5b,<cls6b,<cls7b
tab_clear_sprite_1_high    .byte >cls0b,>cls1b,>cls2b,>cls3b,>cls4b,>cls5b,>cls6b,>cls7b


cls0b
    sta pmadr+$500+$11,x

    sta pmadr+$500+$10,x

    sta pmadr+$500-8,x
    sta pmadr+$500-7,x
    sta pmadr+$500-6,x
    sta pmadr+$500-5,x
    sta pmadr+$500-4,x
    sta pmadr+$500-3,x
    sta pmadr+$500-2,x
    sta pmadr+$500-1,x


    rts

cls1b
    sta pmadr+$500+$13,x
    sta pmadr+$500+$14,x
    sta pmadr+$500+$15,x
    sta pmadr+$500+$16,x
    sta pmadr+$500+$17,x
    sta pmadr+$500+$18,x
    jmp cls7b_36


cls2b
    sta pmadr+$500+$13,x
    sta pmadr+$500+$14,x
    sta pmadr+$500+$15,x
    sta pmadr+$500+$16,x
    sta pmadr+$500+$17,x
    jmp cls7b_30

cls3b
    sta pmadr+$500+$13,x
    sta pmadr+$500+$14,x
    sta pmadr+$500+$15,x
    sta pmadr+$500+$16,x
    jmp cls7b_24

cls4b
    sta pmadr+$500+$13,x
    sta pmadr+$500+$14,x
    sta pmadr+$500+$15,x
    jmp cls7b_18

cls5b
;    cpx #POSY_MAX-32
;    bcs cls7b_12
    sta pmadr+$500+$13,x
    sta pmadr+$500+$14,x
    jmp cls7b_12


cls6b
    sta pmadr+$500+$13,x
    jmp cls7b_6

cls7b
    sta pmadr+$500-7,x
cls7b_6
    sta pmadr+$500-6,x
cls7b_12
    sta pmadr+$500-5,x
cls7b_18
    sta pmadr+$500-4,x
cls7b_24
    sta pmadr+$500-3,x
cls7b_30
    sta pmadr+$500-2,x
cls7b_36
    sta pmadr+$500-1,x

    sta pmadr+$500+$10,x
    sta pmadr+$500+$11,x
    sta pmadr+$500+$12,x
    rts


tab_clear_sprite_2_low    .byte <cls0c,<cls1c,<cls2c,<cls3c,<cls4c,<cls5c,<cls6c,<cls7c
tab_clear_sprite_2_high    .byte >cls0c,>cls1c,>cls2c,>cls3c,>cls4c,>cls5c,>cls6c,>cls7c


cls0c
    sta pmadr+$600+$11,x

    sta pmadr+$600+$10,x

    sta pmadr+$600-8,x
    sta pmadr+$600-7,x
    sta pmadr+$600-6,x
    sta pmadr+$600-5,x
    sta pmadr+$600-4,x
    sta pmadr+$600-3,x
    sta pmadr+$600-2,x
    sta pmadr+$600-1,x


    rts

cls1c
    sta pmadr+$600+$13,x
    sta pmadr+$600+$14,x
    sta pmadr+$600+$15,x
    sta pmadr+$600+$16,x
    sta pmadr+$600+$17,x
    sta pmadr+$600+$18,x
    jmp cls7c_36


cls2c
    sta pmadr+$600+$13,x
    sta pmadr+$600+$14,x
    sta pmadr+$600+$15,x
    sta pmadr+$600+$16,x
    sta pmadr+$600+$17,x
    jmp cls7c_30

cls3c
    sta pmadr+$600+$13,x
    sta pmadr+$600+$14,x
    sta pmadr+$600+$15,x
    sta pmadr+$600+$16,x
    jmp cls7c_24

cls4c
    sta pmadr+$600+$13,x
    sta pmadr+$600+$14,x
    sta pmadr+$600+$15,x
    jmp cls7c_18

cls5c
;    cpx #POSY_MAX-32
;    ccs cls7c_12
    sta pmadr+$600+$13,x
    sta pmadr+$600+$14,x
    jmp cls7c_12


cls6c
    sta pmadr+$600+$13,x
    jmp cls7c_6

cls7c
    sta pmadr+$600-7,x
cls7c_6
    sta pmadr+$600-6,x
cls7c_12
    sta pmadr+$600-5,x
cls7c_18
    sta pmadr+$600-4,x
cls7c_24
    sta pmadr+$600-3,x
cls7c_30
    sta pmadr+$600-2,x
cls7c_36
    sta pmadr+$600-1,x

    sta pmadr+$600+$10,x
    sta pmadr+$600+$11,x
    sta pmadr+$600+$12,x
    rts

tab_clear_sprite_3_low    .byte <cls0d,<cls1d,<cls2d,<cls3d,<cls4d,<cls5d,<cls6d,<cls7d
tab_clear_sprite_3_high    .byte >cls0d,>cls1d,>cls2d,>cls3d,>cls4d,>cls5d,>cls6d,>cls7d


cls0d
    sta pmadr+$700+$11,x

    sta pmadr+$700+$10,x

    sta pmadr+$700-8,x
    sta pmadr+$700-7,x
    sta pmadr+$700-6,x
    sta pmadr+$700-5,x
    sta pmadr+$700-4,x
    sta pmadr+$700-3,x
    sta pmadr+$700-2,x
    sta pmadr+$700-1,x


    rts

cls1d
    sta pmadr+$700+$13,x
    sta pmadr+$700+$14,x
    sta pmadr+$700+$15,x
    sta pmadr+$700+$16,x
    sta pmadr+$700+$17,x
    sta pmadr+$700+$18,x
    jmp cls7d_36


cls2d
    sta pmadr+$700+$13,x
    sta pmadr+$700+$14,x
    sta pmadr+$700+$15,x
    sta pmadr+$700+$16,x
    sta pmadr+$700+$17,x
    jmp cls7d_30

cls3d
    sta pmadr+$700+$13,x
    sta pmadr+$700+$14,x
    sta pmadr+$700+$15,x
    sta pmadr+$700+$16,x
    jmp cls7d_24

cls4d
    sta pmadr+$700+$13,x
    sta pmadr+$700+$14,x
    sta pmadr+$700+$15,x
    jmp cls7d_18

cls5d
;    cpx #POSY_MAX-32
;    ccs cls7d_12
    sta pmadr+$700+$13,x
    sta pmadr+$700+$14,x
    jmp cls7d_12


cls6d
    sta pmadr+$700+$13,x
    jmp cls7d_6

cls7d
    sta pmadr+$700-7,x
cls7d_6
    sta pmadr+$700-6,x
cls7d_12
    sta pmadr+$700-5,x
cls7d_18
    sta pmadr+$700-4,x
cls7d_24
    sta pmadr+$700-3,x
cls7d_30
    sta pmadr+$700-2,x
cls7d_36
    sta pmadr+$700-1,x

    sta pmadr+$700+$10,x
    sta pmadr+$700+$11,x
    sta pmadr+$700+$12,x
    rts

; NACHTEILE:
; die Spritenummer, die beschrieben werden soll ist in die Funktion hineinkodiert (+$400, +$500)
;

;;  14 lda a 2 cycles sum:28
;;  32 sta a 5 cycles sum:160
;;; sum 160 + 28 + 12 (jsr/rts) fuer 2 pmadr (16 Bytes, 2 Sprites)
;;;     200 ~57% schneller als eine einfache Copy Schleife
;;; 200 * 8 ~1600 Cycles
;;;
;;; worst case, wenn sich das LDA nicht wiederholt
;;; 32 lda a 2 cycles sum:64
;;; 32 sta a 5 cycles sum:160
;;; sum 160 + 64 + 12 = 236 ~50% schneller als copy loop

;;;  Das selbe mit einer einfachen Schleife
;;; lda data,y ; 4
;;; sta data0  ; 3
;;; iny        ; 2
;;; lda data,y ; 4
;;; sta data0+1; 3
;;; init ~32 cycles

;;;         ldx #0                  ; 2
;;;         ldy #15                 ; 2
;;; loop
;;;         lda (data0),y           ; 5
;;;         sta pmadr0,x            ; 5
;;;
;;;         lda (data1),y           ; 5
;;;         sta pmadr1,x            ; 5
;;;         inx                     ; 2
;;;
;;;         dey                     ; 2
;;;         bpl loop                ; 3 sum = 27
;;;
;;;  sum 27*16(loop) + 32+4(init) + 12(jsr/rts) = 476
;;;      408 + 36 + 12 = 456 4% schneller 1x unrool loop
;;;  476 * 8 ~3808 cycles

; TODO: WIP
;player0a
; ldy #0
;?loop0a
; lda (data),y
; sta pmadr+$400+0,x
; inx
; iny
; lda (data),y
; sta pmadr+$400+0,x
; inx
; iny
; cpy #16
; bne ?loop0a
; rts
;
;player1a
; ldy #0
;?loop1a
; lda (data),y
; sta pmadr+$500+0,x
; inx
; iny
; lda (data),y
; sta pmadr+$500+0,x
; inx
; iny
; cpy #16
; bne ?loop1a
; rts
;
;player2a
; ldy #0
;?loop2a
; lda (data),y
; sta pmadr+$600+0,x
; inx
; iny
; lda (data),y
; sta pmadr+$600+0,x
; inx
; iny
; cpy #16
; bne ?loop2a
; rts
;
;player3a
; ldy #0               ; 2
;?loop3a
; lda (data),y         ; 5
; sta pmadr+$700+0,x   ; 5
; inx                  ; 2
; iny                  ; 2
; lda (data),y         ; 5
; sta pmadr+$700+0,x   ; 5
; inx                  ; 2
; iny                  ; 2
; cpy #16              ; 2
; bne ?loop3a          ; 3 => sum:33*8 = 264
; rts

player0a
 ldy #0                ; 2
 lda (data),y          ; 5
 sta pmadr+$400+0,x    ; 5
 iny                   ; 2
 lda (data),y
 sta pmadr+$400+1,x
 iny
 lda (data),y
 sta pmadr+$400+2,x
 iny
 lda (data),y
 sta pmadr+$400+3,x
 iny
 lda (data),y
 sta pmadr+$400+4,x
 iny
 lda (data),y
 sta pmadr+$400+5,x
 iny
 lda (data),y
 sta pmadr+$400+6,x
 iny
 lda (data),y
 sta pmadr+$400+7,x
 iny
 lda (data),y
 sta pmadr+$400+8,x
 iny
 lda (data),y
 sta pmadr+$400+9,x
 iny
 lda (data),y
 sta pmadr+$400+10,x
 iny
 lda (data),y
 sta pmadr+$400+11,x
 iny
 lda (data),y
 sta pmadr+$400+12,x
 iny
 lda (data),y
 sta pmadr+$400+13,x
 iny
 lda (data),y
 sta pmadr+$400+14,x
 iny
 lda (data),y
 sta pmadr+$400+15,x
; iny                  ; sum:12*16 = 192 37% faster
 rts

player1a
 ldy #0                ; 2
 lda (data),y          ; 5
 sta pmadr+$500+0,x    ; 5
 iny                   ; 2
 lda (data),y
 sta pmadr+$500+1,x
 iny
 lda (data),y
 sta pmadr+$500+2,x
 iny
 lda (data),y
 sta pmadr+$500+3,x
 iny
 lda (data),y
 sta pmadr+$500+4,x
 iny
 lda (data),y
 sta pmadr+$500+5,x
 iny
 lda (data),y
 sta pmadr+$500+6,x
 iny
 lda (data),y
 sta pmadr+$500+7,x
 iny
 lda (data),y
 sta pmadr+$500+8,x
 iny
 lda (data),y
 sta pmadr+$500+9,x
 iny
 lda (data),y
 sta pmadr+$500+10,x
 iny
 lda (data),y
 sta pmadr+$500+11,x
 iny
 lda (data),y
 sta pmadr+$500+12,x
 iny
 lda (data),y
 sta pmadr+$500+13,x
 iny
 lda (data),y
 sta pmadr+$500+14,x
 iny
 lda (data),y
 sta pmadr+$500+15,x
 rts

player2a
 ldy #0                ; 2
 lda (data),y          ; 5
 sta pmadr+$600+0,x    ; 5
 iny                   ; 2
 lda (data),y
 sta pmadr+$600+1,x
 iny
 lda (data),y
 sta pmadr+$600+2,x
 iny
 lda (data),y
 sta pmadr+$600+3,x
 iny
 lda (data),y
 sta pmadr+$600+4,x
 iny
 lda (data),y
 sta pmadr+$600+5,x
 iny
 lda (data),y
 sta pmadr+$600+6,x
 iny
 lda (data),y
 sta pmadr+$600+7,x
 iny
 lda (data),y
 sta pmadr+$600+8,x
 iny
 lda (data),y
 sta pmadr+$600+9,x
 iny
 lda (data),y
 sta pmadr+$600+10,x
 iny
 lda (data),y
 sta pmadr+$600+11,x
 iny
 lda (data),y
 sta pmadr+$600+12,x
 iny
 lda (data),y
 sta pmadr+$600+13,x
 iny
 lda (data),y
 sta pmadr+$600+14,x
 iny
 lda (data),y
 sta pmadr+$600+15,x
 rts

player3a
 ldy #0                ; 2
 lda (data),y          ; 5
 sta pmadr+$700+0,x    ; 5
 iny                   ; 2
 lda (data),y
 sta pmadr+$700+1,x
 iny
 lda (data),y
 sta pmadr+$700+2,x
 iny
 lda (data),y
 sta pmadr+$700+3,x
 iny
 lda (data),y
 sta pmadr+$700+4,x
 iny
 lda (data),y
 sta pmadr+$700+5,x
 iny
 lda (data),y
 sta pmadr+$700+6,x
 iny
 lda (data),y
 sta pmadr+$700+7,x
 iny
 lda (data),y
 sta pmadr+$700+8,x
 iny
 lda (data),y
 sta pmadr+$700+9,x
 iny
 lda (data),y
 sta pmadr+$700+10,x
 iny
 lda (data),y
 sta pmadr+$700+11,x
 iny
 lda (data),y
 sta pmadr+$700+12,x
 iny
 lda (data),y
 sta pmadr+$700+13,x
 iny
 lda (data),y
 sta pmadr+$700+14,x
 iny
 lda (data),y
 sta pmadr+$700+15,x
 rts

