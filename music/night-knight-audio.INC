;;  Night Knight Audio fuer Game, no music, only some audio

; .include "NOTEN.INC"
  .local

@audio
@night_knight_audio_table
    .word ?audio_Length        ; Zeigt auf 8 Byte Liste [0] ist volle Note,[1] halbe...
    .word ?audio_huellkurven
    .word ?audio_Shapes
    .word 0                    ; 3. Parameter von music_init, wo faengt die Liste der Takte an

; ********************************************************************************
; This must be 8 bytes after the table before :-(
; ********************************************************************************
?audio_Length
       .byte 0,0,0,0,0,0,0,0


; ********************************************************************************
; Liste der Huellkurven
; up to 127 huellkurven
; ********************************************************************************
?audio_huellkurven
  .word 0
  .word ?huell_1_make_yellow                  ; 1
  .word ?huell_2_jump
  .word ?huell_3_inc_score
  .word ?huell_4_inc_score_end
  .word ?huell_5_start_pling
  .word ?huell_6_take_key
  .word ?huell_7_key_occur
  .word ?huell_8_gem_occur
  .word ?huell_9_enter_open_door
  .word ?huell_0a_dude_died
  .word ?huell_0b_TIC
  .word ?huell_0c_arrow
  .word 0
  .word ?huell_EMPTY
  .word ?huell_0f
  .word ?huell_10
  .word ?huell_11
  .word ?huell_12
  .word ?huell_13
  .word 0,0,0,0,0,0,0,0,0,0,0,0

  .word ?huell_20 ; BASS
  .word ?huell_21 ; Normal
  .word ?huell_22 ; Normal Melodie
  .word ?huell_23 ; BASS at 2. position

  .word ?huell_24_hihat_len_2_1late ; 032000
  .word ?huell_25_hihat_len_2       ; 320000
  .word ?huell_26_hihat_len_3       ; 432000
  .word ?huell_27_g4_blink          ; 08888888
  .word ?huell_28_g4                ; 88888888
  .word ?huell_29_hihat_33
  .word ?huell_2a_start
  .word ?huell_2b_start
  .word ?huell_2c_start
  .word ?huell_2d_start

  .word ?huell_2e_end_theme ; 3+4
  .word ?huell_2f_end_theme ; 77770000
;  .word ?huell_30_end_theme
  .word $ffff

; ***************************************************************************
; Adressenliste der Shapes
; up to 127 Shapes (0-126)
; ***************************************************************************
?audio_Shapes
  .word 0
  .word ?shape_1_make_yellow      ; 1 bleibt
  .word ?shape_2_jump             ; 2 bleibt
  .word ?shape_3_inc_score        ; 3 bleibt
  .word ?shape_4_inc_score_end    ; 4 bleibt
  .word ?shape_5_start_pling      ; 5 bleibt
  .word ?shape_6_take_key
  .word ?shape_7_key_occur
  .word ?shape_8_gem_occur
  .word ?shape_9_enter_open_door
  .word ?shape_0a_dude_died ; a bleibt
  .word ?shape_0b_tic
  .word ?shape_0c_arrow
  .word 0
  .word 0
  .word ?shape_0f

  .word ?shape_10
  .word ?shape_11_hihat_23p23
  .word ?shape_12_hihat_2323
  .word ?shape_13_hihat_23233
  .word ?shape_14_hihat_23232
  .word ?shape_15_hihat___223
  .word ?shape_16_hihat_23223
  .word ?shape_17_hihat_23_3
  .word ?shape_18_hihat_2_33233_
  .word ?shape_19_hihat_2_332323
  .word ?shape_1a_hihat_232_
  .word ?shape_1b_hihat_2_2__323
  .word ?shape_1c_2__23___
  .word ?shape_1d_2___3___
  .word 0

  .word ?shape_1f
; Shapes fuer Music - 3f
  .word ?shape_20_1
  .word ?shape_21_1
  .word 0

  .word ?shape_23_2
  .word ?shape_24_3

  .word ?shape_25_4
  .word ?shape_26_4

  .word ?shape_27_6
  .word ?shape_28_6

  .word ?shape_29_8
  .word ?shape_2a_10

  .word ?shape_2b_12
  .word ?shape_2c_12

  .word ?shape_2d_14

  .word ?shape_2e_16
  .word ?shape_2f_16
  .word 0

  .word ?shape_31_17
  .word ?shape_32_18
  .word ?shape_33_19

  .word ?shape_34_20
  .word ?shape_35_20

  .word ?shape_36_31
  .word ?shape_37_32

  .word ?shape_38_33
  .word ?shape_39_34
  .word ?shape_3a_35
  .word ?shape_3b_36

  .word ?shape_3c_40
  .word ?shape_3d_40

  .word ?shape_3e_41
  .word ?shape_3f_42

  .word ?shape_40_01 ; Start Sound
  .word ?shape_41_01
  .word ?shape_42_01

  .word ?shape_43_02
  .word ?shape_44_02
  .word ?shape_45_02

  .word ?shape_46_03

  .word ?shape_47_01 ; Stage geschafft
  .word ?shape_48_01

  .word ?shape_49_02
  .word ?shape_4a_02

  .word ?shape_4b_GameOver
  .word ?shape_4c_GameOver
  .word ?shape_4d_GameOver
  .word ?shape_4e_GameOver
  .word ?shape_4f_GameOver
  .word ?shape_50_GameOver
  .word ?shape_51_hihat_2_______

  .word ?shape_52_01_EndTheme
  .word ?shape_53_01_EndTheme
  .word ?shape_54_01_EndTheme_hihats
  .word ?shape_55_02_EndTheme
  .word ?shape_56_02_EndTheme
  .word ?shape_57_02_EndTheme_hihats
  .word ?shape_58_03_EndTheme_hihats
  .word ?shape_59_04_EndTheme
  .word ?shape_5a_04_EndTheme
  .word ?shape_5b_04_EndTheme_hihats
  .word ?shape_5c_13_EndTheme
  .word ?shape_5d_13_EndTheme
  .word ?shape_5e_15_EndTheme
  .word ?shape_5f_15_EndTheme
  .word ?shape_60_16_EndTheme
  .word ?shape_61_16_EndTheme
  .word ?shape_62_16_EndTheme_hihat
  .word ?shape_63_23_EndTheme
  .word ?shape_64_25_EndTheme
  .word ?shape_65_25_EndTheme
  .word ?shape_66_25_EndTheme_hihat
  .word ?shape_67_26_EndTheme
  .word ?shape_68_26_EndTheme
  .word ?shape_69_26_EndTheme_hihat

  .word $ffff

; ***************************************************************************
; Die eigentlichen Huellkurven
; 1. Nibble ist die Disortion 0,2,4,6,8,a,c,e
; 2. Nibble die Lautstaerke, 0-F ist moeglich
; ist das Vibrabit gesetzt (Bit 4) (eigentlich Laut-only), wird das naechste Byte fuer Vibration verwendet
; Abschluss immer mit ENDE Marke
; ***************************************************************************
; TODO: Herausfinden warum die huellkurve diese Laenge haben muss, sonst piept es
?huell_EMPTY
 .byte $a0,$a0,ENDE

; Dude laeuft ueber den Boden, jeder Boden der gelb wird, erzeugt ein Pling

?huell_1_make_yellow ; 1
 .byte $A6,$A2,$B6,$F7,$A2,$A0,ENDE ; bling blong, sehr flott!

?shape_1_make_yellow
 .byte HUELL,1
 .byte D6,S,ENDE ; Dude laeuft ueber einen nicht gelben Boden

; Dude springt ----------------------------------------------------------------

?huell_2_jump
 .byte $A8
 .byte $A8
 .byte $B4, $0F
 .byte $A4
 .byte $A0
 .byte ENDE

?shape_2_jump
 .byte HUELL,2
 .byte F4,S,ENDE ; Dude springt

; Stage ende, die Sekunden werden runtergezaehlt und erzeugen jede 2. Sekunde ein Pling

?huell_3_inc_score ; 1
 .byte $A6,$A2,$B6,$F7,$A2,$A0,ENDE ; bling blong, sehr flott!

?shape_3_inc_score
 .byte HUELL,3
 .byte D6,S,ENDE

; Stage ende, die Sekunden sind runtergezaehlt ---------------------------------

?huell_4_inc_score_end
 .byte $A8
 .byte $A4
 .byte $B4, $24
 .byte $A2
 .byte $B2, $0A
 .byte $B1, $08
 .byte $A1
 .byte $A0
 .byte ENDE

?shape_4_inc_score_end
 .byte HUELL,4
 .byte A4,E,ENDE

; Firebutton wurde gedrueckt fuer Start Game ----------------------------------------

?huell_5_start_pling
 .byte $A8
 .byte $A4
 .byte $B4, $24
 .byte $A2
 .byte $B2, $0A
 .byte $B1, $08
 .byte $A1
 .byte $A0
 .byte ENDE

?shape_5_start_pling
 .byte HUELL,5
 .byte A4,E,ENDE

; Schluessel eingesammelt -----------------------------------------------------------

?huell_6_take_key
 .byte $A8
 .byte $A4
 .byte $B4, $24
 .byte $A2
 .byte $B2, $0A
 .byte $B1, $08
 .byte $A1
 .byte $A0
 .byte ENDE

?shape_6_take_key
 .byte HUELL,6
 .byte A4,E,ENDE

; Schluessel erscheint -----------------------------------------------------------
?huell_7_key_occur
 .byte $A8
 .byte $B6,$2B
 .byte $B4,$1A
 .byte $A0
 .byte ENDE

?shape_7_key_occur
 .byte HUELL,7
 .byte F4,S,ENDE

; GEM erscheint ------------------------------------------------------------------
?huell_8_gem_occur
 .byte $A8
 .byte $B7,$0D
 .byte $B5,$F2
 .byte $B4,$0D
 .byte $A0
 .byte ENDE

?shape_8_gem_occur
 .byte HUELL,8
 .byte E4,S,ENDE

; DUDE betritt die offene Tuer -----------------------------------------------------
?huell_9_enter_open_door
 .byte $A8
 .byte $B7,$0D
 .byte $B5,$F2
 .byte $B4,$0D
 .byte $90,$1F ; Klingt nur mit G3 vernuenftig sonst hier 1f anpassen
 .byte $80     ; Auf und abklingendes Rauschen, entschwinden durch die Tuer
 .byte $91,$FF
 .byte $91,$01
 .byte $92,$FF
 .byte $92,$01
 .byte $93,$FF
 .byte $93,$01
 .byte $93,$FF
 .byte $92,$01
 .byte $92,$FF
 .byte $92,$01
 .byte $92,$FF
 .byte $92,$01
 .byte $91,$FF
 .byte $91,$01
 .byte $91,$FF
 .byte $91,$01
 .byte $91,$FF
 .byte $91,$01
 .byte $80

 .byte ENDE

?shape_9_enter_open_door
 .byte HUELL,9
 .byte G3,H,ENDE

; Dude stirbt -----------------------------------------------------------------
?huell_0a_dude_died
 .byte $EA
 .byte $E8,$E8
 .byte $E6,$E4
 .byte $E2,$E1
 .byte $E0

; .byte $E8            ; $E0 Timbre wird im Hexenplayer zu $C0 Timbre und spielt smooth BASS
; .byte $E4,$E4
; .byte $E2,$E2
; .byte $E1,$E1
; .byte $E0
 .byte ENDE

; $0a==10
?shape_0a_dude_died
 .byte HUELL,$0A
 .byte A1,E,ENDE      ; tiefester Ton in Timbre $E0 ist

; ------------------------------------------------------------------------------
?huell_0b_TIC
 .byte $A4,$A3,$A2,$A1,$A0,ENDE


?shape_0b_TIC
 .byte HUELL,$0b
 .byte B3,S
 .byte ENDE

?huell_0c_arrow
  .byte $B5,$0B,$A4,$A3,$91,$F4,$82,$84,$83,$82,$81,$80,ENDE

?shape_0c_arrow
  .BYTE HUELL,$0C
  .byte CIS0,Q,ENDE

; -------------------------------------------------------------------------------

; TODO: herausfinden was das war
;;S E Q H F
;?shape_1_intro
; .byte HUELL,$21
; .byte E4,Q
; .byte A3,S
; .byte B3,E
; .byte E4,Q
; .byte DIS4,Q
; .byte AIS3,S
; .byte ENDE

; TEST --------------------------------------------------------------------------

?huell_0f
  .byte $A8,$A8,$A8,$A8,$A7,$A7,$A7,$A7,$A6,$A6,$A6,$A6,$A5,$A5,$A5,$A5,$A4,$A4,$A4,$A4,$A0,ENDE

?shape_0f
@single_shape
  .byte HUELL,$0E
  .byte NIX,H
  .BYTE HUELL,$0f
  .byte C3,E
  .byte G3,E
  .byte G3,Q,ENDE

; ---------------------------------------------------
?huell_10
  .byte 0,0,0,0,0,0,0,0,0,0,ENDE

?shape_10
  .BYTE HUELL,$10
  .byte 0,F,ENDE

?huell_11
  .byte 0,0,0,0,0,0,0,0,0,0,ENDE

?shape_11
  .BYTE HUELL,$11
  .byte 0,F,ENDE


?huell_12
  .byte 0,0,0,0,0,0,0,0,0,0,ENDE

?shape_12
  .BYTE HUELL,$12
  .byte 0,F,ENDE


?huell_13
  .byte 0,0,0,0,0,0,0,0,0,0,ENDE

?shape_13
  .BYTE HUELL,$13
  .byte 0,F,ENDE

; ---------------------------------------------------
?huell_20
  .byte $E7,$E8,$E8,$E8,$E8,$E8,$E7,$E6,$E0,ENDE  ; BASS Huell zum Spielen < B-2
;  .byte $A7,$A8,$A8,$A8,$A8,$A8,$A7,$A6,$A0,$A0,ENDE  ; BASS Huell zum Spielen < B-2

?huell_21
  .byte $A7,$A7,$A7,$A6,$A5,$A4,$A3,$A2,$A0,ENDE  ; Normal Huell

?huell_22
  .byte $A7,$A7,$A7,$A7,$A5,$A4,$A3,$A2,$A0,ENDE  ; Normal Huell

?huell_23
  .byte $E0,$E4,$E8,$E8,$E7,$E7,$E7,$E7,$E0,ENDE  ; BASS Huell zum Spielen < B-2
;  .byte $A0,$A4,$A8,$A8,$A7,$A7,$A7,$A7,$A0,$A0,ENDE  ; BASS Huell zum Spielen < B-2

?huell_24_hihat_len_2_1late
  .byte $00,$86,$83,$00,ENDE

?huell_25_hihat_len_2
  .byte $86,$83,$00,ENDE

?huell_26_hihat_len_3
  .byte $86,$85,$84,$00,ENDE


?huell_27_g4_blink
  .byte $B4,$C0
  .byte $B7,$40
  .byte $A7,$A7,$A7,$A7,$A7,$A7,$A0,ENDE

?huell_28_g4
  .byte $A7,$A7,$A7,$A7,$A7,$A7,$A7,$A7,$A0,ENDE

?huell_29_hihat_33
  .byte $87,$85,$82,$80,$87,$85,$82,$80,ENDE

?huell_2a_start
  .byte $B7,$02,$A7,$B7,$FE,$A7
  .byte $B7,$02,$A7,$B7,$FE,$A7
  .byte $A0,ENDE

?huell_2b_start
  .byte $B4,$D0,$B7,$30,$B7,$02,$A7,$B7,$FE,$A7
  .byte $B7,$02,$A7,$B7,$FE,$A7
  .byte $A0,ENDE

?huell_2c_start
  .byte $A0,$B7,$FD,$A7,$A7,$A7
  .byte $A7,$A7,$A7
  .byte $A0,ENDE

?huell_2d_start
  .byte $B7,$FD,$A7,$A7,$A7
  .byte $A7,$A7,$A7,$A7
  .byte $A0,ENDE

; -------------------------------------------------------
?shape_11_hihat_23p23
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$24 ; len p2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte ENDE

?shape_12_hihat_2323
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte ENDE

?shape_13_hihat_23233
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte 1,E
  .byte ENDE

?shape_14_hihat_23232
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte HUELL,$25 ; len 2
  .byte 1,E
  .byte ENDE

?shape_15_hihat___223
  .byte HUELL,$0E
  .byte NIX,Q
  .byte NIX,Q
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte 1,E
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte ENDE,0

?shape_16_hihat_23223
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$25 ; len 3
  .byte 1,E
  .byte HUELL,$26 ; len 2
  .byte 1,E
  .byte ENDE

?shape_17_hihat_23_3
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte ENDE

?shape_18_hihat_2_33233_
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte 1,E
  .byte HUELL,$25 ; len 2
  .byte 1,E
  .byte HUELL,$25 ; len 3
  .byte 1,E
  .byte 1,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte ENDE


?shape_19_hihat_2_332323
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte 1,E
  .byte HUELL,$25 ; len 2
  .byte 1,E
  .byte HUELL,$25 ; len 3
  .byte 1,E
  .byte HUELL,$25 ; len 2
  .byte 1,E
  .byte HUELL,$25 ; len 3
  .byte 1,E
  .byte ENDE

?shape_1a_hihat_232_
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE

?shape_1b_hihat_2_2__323
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$25 ; len 3
  .byte 1,E
  .byte HUELL,$25 ; len 2
  .byte 1,E
  .byte HUELL,$25 ; len 3
  .byte 1,E
  .byte ENDE

; -------------------------------------------------------
?shape_1f
  .byte HUELL,$20
  .byte NIX,F
  .byte ENDE

; -------------------------------------------------------

?shape_20_1
  .byte HUELL,$21 ; normal
  .byte C3,Q
;  .byte HUELL,$22 ; normal
;  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,Q
  .byte C4,Q
  .byte C3,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte ENDE

?shape_21_1
  .byte HUELL,$20 ; BASS
  .byte C2,H
  .byte HUELL,$23 ; BASS
  .byte G2,H
  .byte ENDE

; --------------------------------------------------------

?shape_23_2
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,Q
  .byte F3,Q
  .byte ENDE

?shape_24_3
  .byte HUELL,$21 ; normal
  .byte C3,Q
  .byte G3,Q
  .byte C4,Q
  .byte C3,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte ENDE

; ---------------------------------------------------

?shape_25_4
  .byte HUELL,$20 ; BASS
  .byte AIS1,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,Q
  .byte HUELL,$20 ; BASS
  .byte AIS1,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte ENDE

?shape_26_4
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$21 ; normal
  .byte F3,H
  .byte ENDE

; ---------------------------------------------------
; shape 5 is like shape 3

?shape_27_6
  .byte HUELL,$21 ; normal
  .byte C3,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,Q
  .byte F3,Q
  .byte ENDE

?shape_28_6
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$20 ; BASS
  .byte G2,H
  .byte ENDE

; shape 7 is like shape 3

?shape_29_8
  .byte HUELL,$21 ; normal
  .byte C3,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$21 ; normal
  .byte C4,E
  .byte G3,Q
  .byte HUELL,$20 ; BASS
  .byte AIS2,Q
  .byte ENDE

; shape 9 is like shape 3

?shape_2a_10
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte C3,Q
  .byte F3,Q
  .byte ENDE

; shape 11 is like shape 3

?shape_2b_12
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE

?shape_2c_12
  .byte HUELL,$20 ; BASS
  .byte AIS1,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte HUELL,$20 ; BASS
  .byte GIS1,Q     ; sollte eigentlich F1 sein
  .byte AIS1,Q
  .byte ENDE

; shape 13 is like shape 3

?shape_2d_14
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,Q
  .byte F3,Q
  .byte ENDE

?shape_2E_16
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte C4,E
  .byte F3,E
  .byte ENDE

?shape_2F_16
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$20 ; BASS
  .byte GIS1,Q   ; sollte F1 sein
  .byte AIS1,Q
  .byte ENDE

; ---------------------------------------------------
?shape_31_17
  .byte HUELL,$21 ; normal
  .byte F3,Q
  .byte C3,Q
  .byte E3,Q
  .byte C3,Q
  .byte ENDE

; ---------------------------------------------------
?shape_32_18
  .byte HUELL,$27 ; g4 blink
  .byte FIS4,E
  .byte G4,E
  .byte HUELL,$28 ; g4
  .byte FIS4,E
  .byte HUELL,$27 ; g4 blink
  .byte G4,E
  .byte HUELL,$28 ; g4
  .byte FIS4,E
  .byte FIS4,E
  .byte G4,E
  .byte G4,E
  .byte ENDE

?shape_33_19
  .byte HUELL,$21 ; normal
  .byte E3,Q
  .byte C3,Q
  .byte E3,Q
  .byte C3,Q
  .byte ENDE

?shape_34_20
  .byte HUELL,$27 ; g4 blink
  .byte DIS4,E
  .byte E4,E
  .byte HUELL,$28 ; g4
  .byte DIS4,E
  .byte HUELL,$27 ; g4 blink
  .byte E4,E
  .byte HUELL,$28 ; g4
  .byte DIS4,E
  .byte DIS4,E
  .byte E4,E
  .byte E4,E
  .byte ENDE

?shape_35_20
  .byte HUELL,$20 ; BASS
  .byte B1,H
  .byte GIS1,Q   ; sollte F1 sein
  .byte AIS1,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte ENDE

?shape_36_31
  .byte HUELL,$20 ; BASS
  .byte C2,H
  .byte G2,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$20 ; BASS
  .byte G2,E
  .byte ENDE

?shape_37_32
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$22 ; normal
  .byte AIS3,E
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,E
  .byte F3,E
  .byte ENDE

?shape_38_33
  .byte HUELL,$28 ; g4
  .byte E4,E
  .byte E4,E
  .byte DIS5,Q
  .byte C5,H
  .byte ENDE

?shape_39_34
  .byte HUELL,$27 ; g4 blink
  .byte FIS4,E
  .byte HUELL,$28 ; g4
  .byte G4,E
  .byte HUELL,$28 ; g4
  .byte FIS4,E
  .byte HUELL,$27 ; g4 blink
  .byte G4,E
  .byte HUELL,$28 ; g4
  .byte FIS4,E
  .byte FIS4,E
  .byte G4,E
  .byte G4,E
  .byte ENDE

?shape_3a_35
  .byte HUELL,$27 ; g4 blink
  .byte E4,E
  .byte HUELL,$28 ; g4
  .byte E4,E
  .byte HUELL,$28 ; g4
  .byte DIS5,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$28 ; g4
  .byte CIS5,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE

?shape_3b_36
  .byte HUELL,$27 ; g4 blink
  .byte DIS4,E
  .byte E4,E
  .byte HUELL,$28 ; g4
  .byte DIS4,E
  .byte E4,E
  .byte C4,E
  .byte C4,E
  .byte HUELL,$28 ; g4
  .byte AIS3,E
  .byte AIS3,E
  .byte ENDE

; --- Shape 40 -----------------------
?shape_3c_40
  .byte HUELL,$27 ; g4 blink
  .byte AIS4,Q
  .byte B4,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$28 ; g4
  .byte AIS4,E

  .byte HUELL,$28
  .byte G4,E
  .byte HUELL,$28 ; g4
  .byte F4,E
  .byte ENDE

?shape_3d_40
  .byte HUELL,$20 ; BASS
  .byte G2,Q
  .byte B2,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte HUELL,$20 ; BASS
  .byte A1,Q
  .byte ENDE

?shape_3e_41
  .byte HUELL,$21 ; normal
  .byte F4,Q
  .byte G3,Q
  .byte C4,Q
  .byte C3,E
  .byte HUELL,$22
  .byte AIS3,E
  .byte ENDE

?shape_3f_42
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22
  .byte AIS3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$22
  .byte A3,E
  .byte HUELL,$21
  .byte G3,Q
  .byte F3,Q
  .byte ENDE

; ----- Shape Start Sound -------------
?shape_1c_2__23___
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$25 ; len 2
  .byte 1,E
  .byte HUELL,$26 ; len 3
  .byte 1,H
  .byte ENDE

?shape_1d_2___3___
  .byte HUELL,$25 ; len 2
  .byte 1,H
  .byte HUELL,$26 ; len 3
  .byte 1,H
  .byte ENDE

;?shape_40_01
;  .byte HUELL,$28 ; g4
;  .byte D4,E
;  .byte E4,E
;  .byte E4,E
;  .byte AIS4,E
;  .byte B4,Q
;  .byte E4,E
;  .byte E4,E
;  .byte ENDE
;
;?shape_41_01
;  .byte HUELL,$28 ; g4
;  .byte E5,Q
;  .byte HUELL,$0E
;  .byte NIX,E
;  .byte HUELL,$28 ; g4
;  .byte A3,E
;  .byte B3,H
;  .byte ENDE
;
;?shape_42_01
;  .byte HUELL,$20 ; BASS
;  .byte E2,Q
;  .byte HUELL,$0E
;  .byte NIX,E
;  .byte HUELL,$20 ; BASS
;  .byte AIS1,E
;  .byte B2,H
;  .byte ENDE
;
;?shape_43_02
;  .byte HUELL,$28 ; g4
;  .byte DIS4,E
;  .byte DIS4,E
;  .byte HUELL,$0E
;  .byte NIX,Q
;  .byte HUELL,$28 ; g4
;  .byte B4,E
;  .byte B4,E
;  .byte HUELL,$0E
;  .byte NIX,Q
;  .byte ENDE
;
;?shape_44_02
;  .byte HUELL,$28 ; g4
;  .byte C5,E
;  .byte C5,E
;  .byte HUELL,$0E
;  .byte NIX,Q
;  .byte HUELL,$28 ; g4
;  .byte G3,E
;  .byte G3,E
;  .byte HUELL,$0E
;  .byte NIX,Q
;  .byte ENDE
;
;?shape_45_02
;  .byte HUELL,$20 ; BASS
;  .byte AIS1,H
;  .byte E2,H
;  .byte ENDE
;
;?shape_46_03
;  .byte HUELL,$0E
;  .byte NIX,H
;  .byte NIX,H
;  .byte ENDE

?shape_40_01
  .byte HUELL,$2b ; g4
  .byte E4,E
  .byte HUELL,$2a ; g4
  .byte E4,E
  .byte E4,E
  .byte HUELL,$2b ; g4
  .byte AIS4,E
  .byte B4,Q
  .byte E4,E
  .byte HUELL,$2a ; g4
  .byte E4,E
  .byte ENDE

?shape_41_01
  .byte HUELL,$20
  .byte E2,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$2a
  .byte B2,E
  .byte C3,H
  .byte ENDE

?shape_42_01
  .byte HUELL,$2a
  .byte B3,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$2a
  .byte A3,E
  .byte B3,H
  .byte ENDE

?shape_43_02
  .byte HUELL,$2b
  .byte C5,E
  .byte HUELL,$2a
  .byte C5,E
  .byte C5,E
  .byte C5,E
  .byte HUELL,$2c
  .byte C5,E
  .byte HUELL,$2d
  .byte C5,E
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE

?shape_44_02
  .byte HUELL,$2a ; g4
  .byte DIS4,E
  .byte DIS4,E
  .byte DIS4,E
  .byte DIS4,E
  .byte HUELL,$2a ; g4
  .byte G3,E
  .byte G3,E
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE

?shape_45_02
  .byte HUELL,$20 ; BASS
  .byte C2,H
  .byte E2,H
  .byte ENDE

?shape_46_03
  .byte HUELL,$0E
  .byte NIX,H
  .byte NIX,H
  .byte ENDE


; ----- Stage geschafft ---------------------
?shape_47_01
  .byte HUELL,$21 ; normal
  .byte E4,Q
  .byte B3,Q
  .byte E3,E
  .byte E3,E
  .byte FIS3,Q
  .byte ENDE

?shape_48_01
  .byte HUELL,$20 ; BASS
  .byte E2,H
  .byte HUELL,$23 ; BASS
  .byte G2,H
  .byte ENDE


?shape_49_02
  .byte HUELL,$21 ; normal
  .byte E3,Q
  .byte DIS4,Q
  .byte E4,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE

?shape_4a_02
  .byte HUELL,$20 ; BASS
  .byte B2,Q

  .byte HUELL,$0E ; normal
  .byte NIX,E
  .byte HUELL,$29 ; len 33
  .byte 1,E
  .byte HUELL,$23 ; BASS
  .byte E2,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE

; NEW Start Sound
?shape_4b_GameOver
  .byte HUELL,$2b ; g4
  .byte C5,E
  .byte HUELL,$2a ; g4
  .byte C5,E
  .byte HUELL,$2b ; g4
  .byte B4,E
  .byte HUELL,$2a ; g4
  .byte B4,E
  .byte HUELL,$2b ; g4
  .byte A4,E
  .byte HUELL,$2a ; g4
  .byte A4,E
  .byte HUELL,$2b ; g4
  .byte G4,E
  .byte HUELL,$2a ; g4
  .byte G4,E
  .byte ENDE

?shape_4c_GameOver
  .byte HUELL,$20 ; g4
  .byte AIS2,Q
  .byte B2,Q
  .byte A2,Q
  .byte HUELL,$2a ; g4
  .byte G3,Q
  .byte ENDE

?shape_4d_GameOver
  .byte HUELL,$21 ; normal
  .byte AIS3,E
  .byte HUELL,$21 ; normal
  .byte D3,E
  .byte HUELL,$21 ; normal
  .byte AIS4,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$21 ; normal
  .byte A3,E
  .byte HUELL,$21 ; normal
  .byte G3,E
  .byte HUELL,$20 ; BASS
  .byte G2,E
  .byte ENDE

?shape_4e_GameOver
  .byte HUELL,$2b ; g4
  .byte E4,E
  .byte HUELL,$2a ; g4
  .byte E4,E
  .byte HUELL,$0E
  .byte NIX,Q
  .byte NIX,H
  .byte ENDE

?shape_4f_GameOver
  .byte HUELL,$20 ; BASS
  .byte E2,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte NIX,H
  .byte ENDE

?shape_50_GameOver
  .byte HUELL,$2b
  .byte B3,E
  .byte HUELL,$2a
  .byte B3,E
  .byte B3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte NIX,H
  .byte ENDE

?shape_51_hihat_2_______
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte NIX,H
  .byte ENDE

@audio_takt_night_knight_game_over
    .byte AUDIO_INIT, SPEED_1, AUDCTL_64K, ~00001111 ; Hi-Speed

    .byte $40,$41,$42,$1c ; GameOver Musik S1
    .byte $43,$44,$45,$1d
    .byte $4b,$4c,$4d,$12
    .byte $4e,$4f,$50,$51
    .byte ENDE,0,0,0

@audio_takt_night_knight_start_game
    .byte AUDIO_INIT, SPEED_1, AUDCTL_64K, ~00001111 ; Hi-Speed
; braucht alle 4 Kanaele zum abspielen!
    .byte $40,$41,$42,$1c ; Start Musik S1
    .byte $43,$44,$45,$1d
    .byte ENDE,0,0,0

@audio_takt_night_knight_stage_done
    .byte AUDIO_INIT, SPEED_1, AUDCTL_64K, ~00001110 ; Hi-Speed
    .byte 0,$47,$48,$12 ; Stage geschafft
    .byte 0,$49,$4a,$1a
    .byte ENDE,0,0,0

@audio_takt_night_knight_music
    .byte AUDIO_INIT, SPEED_1, AUDCTL_64K, ~00001110 ; Hi-Speed

    .byte 0,$20,$21,$11 ; S1
    .byte 0,$23,$21,$12 ; S2
    .byte 0,$24,$21,$11 ; S3
    .byte 0,$25,$26,$13 ; S4
    .byte 0,$24,$21,$12 ; S5
    .byte 0,$27,$28,$11 ; S6
    .byte 0,$24,$21,$12 ; S7
    .byte 0,$29,$26,$13 ; S8

    .byte 0,$24,$21,$11 ; S9
    .byte 0,$2A,$21,$12 ; S10
    .byte 0,$24,$21,$11 ; S11
    .byte 0,$2B,$2C,$13 ; S12

    .byte 0,$24,$21,$12 ; S13
    .byte 0,$2D,$21,$11 ; S14
    .byte 0,$24,$21,$14 ; S15 wie S13

; start  Duedel Duedel Dueueuedel
    .byte 0,$2E,$2F,$15 ; S16
    .byte 0,$31,$21,$11 ; S17
    .byte 0,$32,$21,$12 ; S18
    .byte 0,$33,$21,$11 ; S19
    .byte 0,$34,$35,$16 ; S20
    .byte 0,$33,$21,$12 ; S21 wie S19
    .byte 0,$32,$21,$17 ; S22 wie S18
    .byte 0,$33,$21,$12 ; S23 wie S19
    .byte 0,$34,$35,$16 ; S24 wie S20
    .byte 0,$24,$21,$11 ; S25 wie S13
    .byte 0,$2D,$21,$12 ; S26
    .byte 0,$24,$21,$11 ; S27 wie S11
    .byte 0,$2B,$2C,$13 ; S28 wie S12
    .byte 0,$24,$21,$12 ; S29 wie S13
    .byte 0,$2D,$21,$11 ; S30 wie S14
    .byte 0,$24,$36,$14 ; S31

; start  Duedel Duedel Dueueuedel #2
    .byte 0,$37,$2F,$15 ; S32 ok
    .byte 0,$38,$21,$11 ; S33
    .byte 0,$39,$21,$18 ; S34
    .byte 0,$38,$21,$12 ; S35 fast wie 33
    .byte 0,$3b,$2C,$19 ; S36
    .byte 0,$38,$21,$11 ; S37 wie 33
    .byte 0,$39,$21,$18 ; S38
    .byte 0,$38,$21,$1a ; S39 fast wie 37
    .byte 0,$3c,$3d,$1b ; S40
    .byte 0,$3e,$21,$11 ; S41
    .byte 0,$3f,$21,$12 ; S42

    .byte JUMP,1,0,0

?shape_52_01_EndTheme
  .byte HUELL,$21 ; normal
  .byte E4,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$21 ; normal
  .byte B3,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE

?shape_53_01_EndTheme

  .byte HUELL,$20 ; BASS
  .byte E2,F
  .byte ENDE

?shape_54_01_EndTheme_hihats
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE


?shape_55_02_EndTheme
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$21 ; normal
  .byte E4,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$21 ; normal
  .byte B4,H
  .byte ENDE

?shape_56_02_EndTheme
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$20 ; BASS
  .byte D2,H
  .byte ENDE

?huell_2e_end_theme
  .byte 0,0,0,0
  .byte $86,$85,$84,$00,ENDE

?shape_57_02_EndTheme_hihats
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte HUELL,$2E
  .byte 1,Q
  .byte HUELL,$26 ; len 3
  .byte 1,H
  .byte ENDE

?shape_58_03_EndTheme_hihats
  .byte HUELL,$0E
  .byte NIX,Q
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE

?shape_59_04_EndTheme
  .byte HUELL,$21 ; normal
  .byte C4,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$21 ; normal
  .byte B3,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE

?shape_5a_04_EndTheme
  .byte HUELL,$20 ; BASS
  .byte C2,F
  .byte ENDE

?shape_5b_04_EndTheme_hihats
  .byte HUELL,$25 ; len 2
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE

?shape_5c_13_EndTheme
  .byte HUELL,$28 ; dauerton
  .byte B4,E
  .byte B4,E
  .byte B4,E
  .byte E4,E
  .byte E4,E
  .byte E4,E
  .byte HUELL,$27 ; blink dauerton
  .byte E5,E
  .byte HUELL,$2F
  .byte E5,E
  .byte ENDE

?huell_2f_end_theme ; 77770000
  .byte $A7,$A7,$A7,$A7,$A0,ENDE

?shape_5d_13_EndTheme
  .byte HUELL,$20 ; BASS
  .byte E2,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$28 ; dauerton
  .byte B4,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE

?shape_5e_15_EndTheme
  .byte HUELL,$0E
  .byte NIX,H
  .byte NIX,E
  .byte HUELL,$27 ; blink dauerton
  .byte B4,E
  .byte HUELL,$2F ; 77770000
  .byte B4,Q
  .byte ENDE

?huell_30_g4_blink
  .byte 0,0,0,0
  .byte $B4,$C0
  .byte $B7,$40
  .byte $A7,$A7,$A0,ENDE

?shape_5f_15_EndTheme
  .byte HUELL,$0E
  .byte NIX,H
  .byte NIX,Q
  .byte HUELL,$30 ; 0000X777 X fuer stottern
  .byte G4,E
  .byte HUELL,$28 ; dauerton
  .byte G4,E
  .byte ENDE

?shape_60_16_EndTheme
  .byte HUELL,$28
  .byte B4,E
  .byte HUELL,$2F ; 77770000
  .byte B4,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$28
  .byte E4,E
  .byte E4,E
  .byte E4,E
  .byte HUELL,$27 ; blink dauerton
  .byte E5,E
  .byte HUELL,$2F
  .byte E5,E
  .byte ENDE

?shape_61_16_EndTheme
  .byte HUELL,$28
  .byte B2,E
  .byte HUELL,$0E
  .byte NIX,Q
  .byte HUELL,$28
  .byte B3,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE

?shape_62_16_EndTheme_hihat
  .byte HUELL,$0E
  .byte NIX,Q
  .byte NIX,E
  .byte HUELL,$26 ; len 3
  .byte 1,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte ENDE

?shape_63_23_EndTheme
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$20 ; BASS
  .byte B1,H
  .byte ENDE

?shape_64_25_EndTheme
  .byte HUELL,$28
  .byte E4,E
  .byte HUELL,$2F ; 77770000
  .byte E4,E
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$28 ; dauerton
  .byte D5,E
  .byte D5,E
  .byte ENDE

?shape_65_25_EndTheme
  .byte HUELL,$20 ; BASS
  .byte E2,H
  .byte HUELL,$0E
  .byte NIX,Q
  .byte HUELL,$20 ; BASS
  .byte E2,Q
  .byte ENDE

?shape_66_25_EndTheme_hihat
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,H
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte ENDE

?shape_67_26_EndTheme
  .byte HUELL,$28 ; dauerton
  .byte D5,E
  .byte B4,E
  .byte B4,E
  .byte B4,E
  .byte E5,E
  .byte E5,E
  .byte E5,E
  .byte E5,E
  .byte ENDE

?shape_68_26_EndTheme
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$20 ; BASS
  .byte E2,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$28 ; dauerton
  .byte E3,E
  .byte E3,E
  .byte E3,E
  .byte HUELL,$0E
  .byte NIX,E
  .byte ENDE

?shape_69_26_EndTheme_hihat
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,E
  .byte HUELL,$26 ; len 3
  .byte 1,Q
  .byte HUELL,$0E
  .byte NIX,Q
  .byte ENDE


@audio_takt_night_knight_end_theme
    .byte AUDIO_INIT, SPEED_0, AUDCTL_64K, ~00001110 ; Hi-Speed

    .byte 0,$52,$53,$54 ; T01
    .byte 0,$55,$56,$57 ; T02
    .byte 0,0,0,$58     ; T03
    .byte 0,$59,$5A,$5B ; T04

    .byte 0,$55,$56,$57 ; T05 wie 02
    .byte 0,0,0,$58     ; T06 wie 03
    .byte 0,$52,$53,$54 ; T07 wie 01

    .byte 0,$55,$56,$57 ; T08 wie 05
    .byte 0,0,0,$58     ; T09 wie 03
    .byte 0,$59,$5A,$5B ; T10 wie 04

    .byte 0,$55,$56,$57 ; T11 wie 05
    .byte 0,0,0,$58     ; T12 wie 03
    .byte 0,$5c,$5d,$5b ; T13

    .byte 0,$55,$56,$57 ; T14 wie 05
    .byte 0,$5e,$5f,$58 ; T15
    .byte 0,$60,$61,$62 ; T16

    .byte 0,$55,$56,$57 ; T17 wie 05
    .byte 0,0,0,$58     ; T18 wie 03
    .byte 0,$5c,$5d,$5b ; T19 wie 13

    .byte 0,$55,$56,$57 ; T20 wie 05
    .byte 0,$5e,$5f,$58 ; T21 wie 15
    .byte 0,$60,$61,$62 ; T22 wie 16 ???

    .byte 0,$55,$63,$57 ; T23
    .byte 0,0,0,$58     ; T24 wie 03
    .byte 0,$64,$65,$66 ; T25

    .byte 0,$67,$68,$69 ; T26

    .byte ENDE,0,0,0
