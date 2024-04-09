;; -*- text -*-
;
; Night Knight Structure
;
; Hier alle Variablen ablegen, die ueberall gebraucht werden

 .local

; Wir verlegen die Structure in Page 5-7, da ist etwas Platz.

; sichern der aktuellen Adresse
?OLD_ADDRESS=*

;
;           OO                              OO
;  OOOOO  OOOOOOO OOOOOO  OO   OO  OOOOO  OOOOOOO OO   OO OOOOOO   OOOOO
; OO        OO    OO   OO OO   OO OO   OO   OO    OO   OO OO   OO OO   OO
;  OOOOO    OO    OO      OO   OO OO        OO    OO   OO OO      OOOOOOO
;      OO   OO    OO      OO   OO OO   OO   OO    OO   OO OO      OO
;  OOOOO     OOOO OO       OOOOOO  OOOOO     OOOO  OOOOOO OO       OOOOO
;

;
;
;
;
; FIND MORE VARIABLES IN MACROS.INC
;
;
;
;

 *=$0600 ; MEMORY_STRUCT this is the earliest point we can use here

@game_mode
 .byte 0

@dude_start_xpos
 .byte 0
@dude_start_ypos
 .byte 0

@seconds
 .byte 0

@level
 .byte 0

@lives
 .byte 0

@live_update
 .byte 0

; timer variable will decrement every frame, if timer arrives 0, seconds will decrement and timer will reset to timercountdown (50pal or 60ntsc)
@timer
 .byte 0

@flicker_enemies
 .byte 0

@shield_protection
 .byte 0

; um einen Flash auszuloesen, einfach 15 reinschreiben
@colbk_flash
 .byte 0

; um einen Player4 Flash auszuloesen, einfach 6 hineinschreiben
@player4_flash
 .byte 0

@headline_color
 .byte 0,0,0,0

@startlevel
 .byte 0

@player_mode
 .byte 0

@play_music
 .byte 1

;
;  OOOOOO  OO     OO  OOOOO OOOOOO
;  OO   OO OO     OO OO       OO
;  OO   OO OO     OO  OOOOO   OO
;  OO   OO OO     OO      OO  OO
;  OO   OO OO     OO      OO  OO
;  OOOOOO  OOOOOO OO  OOOOO   OO
;

;
; Displaylist fuer Night Knight
;
@game_screen = $1ba0

; @title_screen = $1d08 ; bd30-40

@night_letter=$C4B8

@score_status_text=$1f60     ; 4 * 40 bytes

@GAME_DLIST
 .byte DL_E3
; .byte DL_E8
 .byte DL_E2|DL_DLI         ; DLI: ?GAME_DLI_NIGHT_KNIGHT
 .byte DL_E1

 .byte DL_GR15|DL_ADDRES    ;          TITLE NIGHT KNIGHT
 .word @night_letter
 .byte DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15
 .byte DL_GR15|DL_DLI,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15
 .byte DL_GR15|DL_DLI,DL_GR15,DL_GR15,DL_GR15,DL_GR15

 .byte DL_E1|DL_DLI         ; DLI: ?GAME_DLI_2
 .byte DL_E1

 .byte DL_GR0|DL_ADDRES     ; LIVE SCORE STAGE LINE
 .word @score_status_text

 .byte DL_E2|DL_DLI         ; DLI: ?NIGHT_DLI_Stage_line
 .byte DL_E1

 .byte DL_GR12|DL_ADDRES|DL_DLI
 .word @game_screen
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_LOOP
 .word @GAME_DLIST


; Message Display list, shows in the middle of the screen a graphics 0 line
@GAME_MESSAGE_DLIST
 .byte DL_E3
; .byte DL_E8
 .byte DL_E2|DL_DLI
 .byte DL_E1

 .byte DL_GR15|DL_ADDRES    ;          TITLE NIGHT KNIGHT
 .word @night_letter
 .byte DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15
 .byte DL_GR15|DL_DLI,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15,DL_GR15
 .byte DL_GR15|DL_DLI,DL_GR15,DL_GR15,DL_GR15,DL_GR15

 .byte DL_E1|DL_DLI         ; DLI: ?SHOW_MESSAGE_NIGHT_DLI
 .byte DL_E1

 .byte DL_GR0|DL_ADDRES
 .word @score_status_text

 .byte DL_E2|DL_DLI        ; DLI: ?SHOW_MESSAGE_NIGHT_DLI_end_gr0
 .byte DL_E1

 .byte DL_GR12|DL_ADDRES|DL_DLI
 .word @game_screen

 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12
 .byte DL_E2|DL_DLI
 .byte DL_E2
 .byte DL_GR0|DL_ADDRES      ; DLI:?SHOW_MESSAGE_NIGHT_DLI_top_edge
 .word @score_status_text+80
 .byte DL_E4                 ; ?SHOW_MESSAGE_NIGHT_DLI_lower_edge

; .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_ADDRES|DL_DLI
 .word @game_screen+440

 .byte DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_GR12|DL_DLI
 .byte DL_GR12|DL_DLI, DL_GR12|DL_DLI

 .byte DL_LOOP
 .word @GAME_MESSAGE_DLIST



@INTRO_DLIST
 .byte DL_E8
 .byte DL_E8
 .byte DL_E8|DL_DLI         ; DLI: ?INTRO_DLI

 .byte DL_GR0|DL_ADDRES
 .word @game_screen

 .byte DL_GR0|DL_DLI        ; DLI: ?INTRO_DLI_line2
 .byte DL_GR0
 .byte DL_GR0|DL_DLI        ; DLI: ?INTRO_DLI_gr7

 .byte DL_GR7|DL_ADDRES    ; Night Knight Text in big letter
 .word @night_letter
 .byte DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7
 .byte DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7
 .byte DL_GR7,DL_GR7,DL_GR7,DL_GR7,DL_GR7
 .byte DL_E1|DL_DLI
 .byte DL_E2

 .byte DL_GR0|DL_ADDRES
 .word @game_screen+160
 .byte DL_GR8
 .byte DL_E2|DL_DLI
 .byte DL_GR0        ; 6 DLI: ?INTRO_DLI
 .byte DL_GR8
 .byte DL_E2|DL_DLI
 .byte DL_GR0        ; 8 DLI: ?INTRO_DLI
 .byte DL_GR8
 .byte DL_E2|DL_DLI
 .byte DL_GR0        ; 10 DLI: ?INTRO_DLI
 .byte DL_GR8
 .byte DL_E8
 .byte DL_E4|DL_DLI
 .byte DL_GR0        ; 12 DLI: ?INTRO_DLI
 .byte DL_GR8
 .byte DL_E1|DL_DLI
 .byte DL_GR0        ; 14 DLI: ?INTRO_DLI
 .byte DL_GR8
 .byte DL_E8|DL_DLI
 .byte DL_GR0        ; 16 DLI: ?INTRO_DLI
 .byte DL_GR8
 .byte DL_E3|DL_DLI
 .byte DL_GR0        ; 18 DLI: ?INTRO_DLI
 .byte DL_GR8
 .byte DL_E8|DL_DLI
 .byte DL_GR0        ; 20 DLI: ?INTRO_DLI

 .byte DL_LOOP
 .word @INTRO_DLIST


@castle=$cb00

@OUTRO_DLIST
 .byte DL_E8
 .byte DL_E8
 .byte DL_E8|DL_DLI        ; DLI: ?OUTRO_DLI

 .byte DL_GR0|DL_ADDRES    ; 0
 .word @game_screen

 .byte DL_E2|DL_DLI        ; DLI: ?OUTRO_DLI_gr13
 .byte DL_E2

 .byte DL_GR13|DL_ADDRES   ; Night Knight Castle in big letter
 .word @castle
 .byte DL_GR13,DL_GR13,DL_GR13,DL_GR13,DL_GR13,DL_GR13,DL_GR13
 .byte DL_E4|DL_DLI

; Zeile 19
 .byte DL_GR0|DL_ADDRES    ; 1
 .word @game_screen+40

 .byte DL_E2|DL_DLI
; 20
 .byte DL_GR0              ; 2 DLI: ?OUTRO_DLI
 .byte DL_E8|DL_DLI
 .byte DL_GR0              ; 3 DLI: ?OUTRO_DLI
 .byte DL_E2|DL_DLI
 .byte DL_GR0              ; 4 DLI: ?OUTRO_DLI
 .byte DL_E2|DL_DLI
 .byte DL_GR0              ; 5 DLI: ?OUTRO_DLI

 .byte DL_LOOP
 .word @OUTRO_DLIST

;?night_knight_text_gfx
; These are the bytes for Night Knight Gfx Text down in Charset, we can reuse 'ight'
; find the bytes in the night-knight-font.wnf
;                            N      i  g     h     t      K     n      i  g     h     t
; .byte 0,0,0,0,0,0,0,0,0,0,0,62,63, 64,65,66,67,68,69,0,0,78,79,80,81, 64,65,66,67,68,69,0,0,0,0,0,0,0,0,0
; .byte 0,0,0,0,0,0,0,0,0,0,0,70,71, 72,73,74,75,76,77,0,0,82,83,84,85, 72,73,74,75,76,77,0,0,0,0,0,0,0,0,0

  .if * >= $6fe
    .error "Memory overflow in page 6! * must < $6fe"
  .endif

; Etwas Speicher fuer die WALL Simulation wenn die GAME_MESSAGE gezeigt wird
 *=$700
@wall_left
 *=*+16

@wall_left_2
 *=*+16

; wiederherstellen der aktuellen Adresse
 *=?OLD_ADDRESS

