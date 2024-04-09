; cdw by 'The Atari Team' 1990-2022

; Routinen kopieren Bloecke auf den Screen
; @drawblock1x2(from, screen)
; @drawblock2x2
; @drawblock3x2
; die FROM Daten liegen linear vor (2,4 oder 6 Bytes hintereinander)
; In den Screen wird aber 1,2 oder 3 Bytes nebeneinander und nochmal 40Bytes weiter geschrieben

; Sichern eines Screenbereiches (screen) in einen Buffer (TO)
; @storeblock1x2(screen, to)
; @storeblock2x2(screen, to)
; die TO Daten liegen linear im Speicher (2,4 Bytes)
; aus dem Screen werden 2 Zeilen mit 40Bytes abstand gelesen
;

 .local

?gem_init
@gem_xpos .byte 0,0,0,0
@gem_ypos .byte 0,0,0,0
@gem_color .byte 0,0,0,0

@gem_occured .byte 0,0,0,0 ; 1 wenn das GEM erschienen ist
@gem_removed .byte 0,0,0,0 ; 1 wenn es removed wurde
@gem_occur_in_second .byte 0,0,0,0 ; sekunde in der ein GEM erscheinen soll
@gem_remove_in_second .byte 0,0,0,0 ; sekunde in der ein GEM wieder verschwinden soll

@initGemsData
 lda #0
 ldy #19
?loop_init
 sta ?gem_init,y
 dey
 bpl ?loop_init
 rts

;  if random < 128 then
;  begin
;    gem_occur_in_second[1]
;    gem_occur_in_second[3]
;  end
;
;  if random < 128 then
;  begin
;    gem_occur_in_second[0]
;    gem_occur_in_second[2]
;  end

; Randomize the occurence in second
; we initialize the gems before to occur in second 15, 25, 35, 45 with + random(10)
; so the earliest occurence of a gem is sec 54, the latest is sec 15
; due to the difference of 10 seconds each and max 9 seconds add, there will never occur
; 2 GEMs at the same time.

; This function randomize the type of occurence by 50% it will swap 2 gems
@gem_occur_randomize
  lda random
  cmp #128
  bcc ?smaller
  lda @gem_occur_in_second+0
  ldx @gem_occur_in_second+2
  sta @gem_occur_in_second+2
  stx @gem_occur_in_second+0
?smaller

  lda random
  cmp #128
  bcc ?smaller2
  lda @gem_occur_in_second+1
  ldx @gem_occur_in_second+3
  sta @gem_occur_in_second+3
  stx @gem_occur_in_second+1
?smaller2

  lda random
  cmp #128
  bcc ?smaller3
  lda @gem_occur_in_second+0
  ldx @gem_occur_in_second+3
  sta @gem_occur_in_second+3
  stx @gem_occur_in_second+0
?smaller3

  lda random
  cmp #128
  bcc ?smaller4
  lda @gem_occur_in_second+1
  ldx @gem_occur_in_second+2
  sta @gem_occur_in_second+2
  stx @gem_occur_in_second+1
?smaller4
  rts

;@gem_screen
;@gem_screen_low .byte 0,0,0,0
;@gem_screen_high .byte 0,0,0,0

@key_screen .word 0

@key_background
 .byte 0,0
@key_image
 .byte KEY_1,KEY_2

@key_ypos_for_color .byte 0
@key_occured .byte 0

@door_screen .word 0
@door_closed_image
 .byte DOOR_CLOSED_1,DOOR_CLOSED_2,DOOR_CLOSED_3,DOOR_CLOSED_4,DOOR_CLOSED_5,DOOR_CLOSED_6

@door_open_image
 .byte DOOR_OPENED_1,DOOR_OPENED_2,DOOR_OPENED_3,DOOR_OPENED_4,DOOR_OPENED_5,DOOR_OPENED_6

@sandclock_screen .word 0
@sandclock_background
 .byte 0,0,0,0
@sandclock_image
 .byte SANDCLOCK_1,SANDCLOCK_2,SANDCLOCK_3,SANDCLOCK_4
@sandclock_ypos_for_color .byte 0
@sandclock_occured .byte 0

@stopwatch_screen .word 0
@stopwatch_background
 .byte 0,0,0,0
@stopwatch_image
 .byte STOPWATCH_1,STOPWATCH_2,STOPWATCH_3,STOPWATCH_4
@stopwatch_ypos_for_color .byte 0
@stopwatch_occured .byte 0

@shield_screen .word 0
@shield_background
 .byte 0,0,0,0
@shield_image
 .byte SHIELD_1,SHIELD_2,SHIELD_3,SHIELD_4
@shield_ypos_for_color .byte 0
@shield_occured .byte 0

@gems_screen .word 0
@gems_background
 .byte 0,0,0,0
@gems_image
 .byte GEMS_1,GEMS_2,GEMS_3,GEMS_4
@gems_ypos_for_color .byte 0
@gems_occured .byte 0

?screen = @REG
?from_screen = @REG+2
?to_background = @REG+2

?parameter_from_screen_and_screen
 ldy #1
 lda (@heap_ptr),y
 sta ?from_screen
 iny
 lda (@heap_ptr),y
 sta ?from_screen+1

 iny
 lda (@heap_ptr),y
 sta ?screen
 iny
 lda (@heap_ptr),y
 sta ?screen+1
 rts

@drawblock1x2
@drawblock1x2_ii
 jsr ?parameter_from_screen_and_screen

 ldy #0
 lda (?from_screen),y
 sta (?screen),y

 iny ; statt ldy #1
 lda (?from_screen),y
 ldy #40
 sta (?screen),y
 rts

; @drawblock2x2(adr:sandclock_background, sandclock_screen)
; kopiert einen 2x2 Buffer (4 Bytes) in den Screen mit +0,+1,+40,+41
@drawblock2x2
@drawblock2x2_ii
 jsr ?parameter_from_screen_and_screen

 ldy #0
 lda (?from_screen),y
 sta (?screen),y
 iny ; #1
 lda (?from_screen),y
 sta (?screen),y

 iny ; #2
 lda (?from_screen),y
 ldy #40
 sta (?screen),y

 ldy #3
 lda (?from_screen),y
 ldy #41
 sta (?screen),y
 rts

; @drawblock3x2(adr:sandclock_background, sandclock_screen)
; kopiert einen 3x2 Buffer (6 Bytes) in den Screen mit +0,+1,+2,+40,+41,+42
@drawblock3x2
@drawblock3x2_ii
 jsr ?parameter_from_screen_and_screen

 ldy #0
 lda (?from_screen),y
 sta (?screen),y
 iny ; #1
 lda (?from_screen),y
 sta (?screen),y
 iny ; #2
 lda (?from_screen),y
 sta (?screen),y

 ldy #3
 lda (?from_screen),y
 ldy #40
 sta (?screen),y

 ldy #4
 lda (?from_screen),y
 ldy #41
 sta (?screen),y

 ldy #5
 lda (?from_screen),y
 ldy #42
 sta (?screen),y
 rts

?parameter_screen_and_to_background
 ldy #1
 lda (@heap_ptr),y
 sta ?screen
 iny
 lda (@heap_ptr),y
 sta ?screen+1

 iny
 lda (@heap_ptr),y
 sta ?to_background
 iny
 lda (@heap_ptr),y
 sta ?to_background+1
 rts

; store to background
; @storeblock1x2(sandclock_screen, adr:sandclock_background)
; kopiert einen 1x2 Buffer (2 Bytes) in den Screen mit +0,+40
@storeblock1x2
@storeblock1x2_ii
 jsr ?parameter_screen_and_to_background

 ldy #0
 lda (?screen),y
 sta (?to_background),y

 ldy #40
 lda (?screen),y
 ldy #1
 sta (?to_background),y
 rts

; store to background
; @storeblock2x2(sandclock_screen, adr:sandclock_background)
; kopiert einen 2x2 Buffer (4 Bytes) in den Screen mit +0,+1,+40,+41
@storeblock2x2
@storeblock2x2_ii
 jsr ?parameter_screen_and_to_background

 ldy #0
 lda (?screen),y
 sta (?to_background),y
 iny ; #1
 lda (?screen),y
 sta (?to_background),y

 ldy #40
 lda (?screen),y
 ldy #2
 sta (?to_background),y

 ldy #41
 lda (?screen),y
 ldy #3
 sta (?to_background),y
 rts

@init_gems
 lda #0
 ldx #3
?loop
 sta @gem_occured,x
 sta @gem_removed,x
 sta @gem_remove_in_second,x
 sta @gem_occur_in_second,x
 dex
 bpl ?loop
 rts

; prueft alle Gems durch, ob eins erscheinen soll
@check_if_gem_occur_in_second
@check_if_gem_occur_in_second_i
 ldy #1
 lda (@heap_ptr),y

 cmp @gem_occur_in_second
 beq ?gem0_occured

 cmp @gem_occur_in_second+1
 beq ?gem1_occured

 cmp @gem_occur_in_second+2
 beq ?gem2_occured

 cmp @gem_occur_in_second+3
 beq ?gem3_occured

?already_occured
 ldy #255 ; nichts erscheint
 ldx #255
 rts

?gem0_occured
 lda @gem_occured
 bne ?already_occured

 ldy #0
 ldx #0
 rts

?gem1_occured
 lda @gem_occured+1
 bne ?already_occured
 ldy #1
 ldx #0
 rts

?gem2_occured
 lda @gem_occured+2
 bne ?already_occured
 ldy #2
 ldx #0
 rts

?gem3_occured
 lda @gem_occured+3
 bne ?already_occured
 ldy #3
 ldx #0
 rts

@check_if_gem_remove_in_second
@check_if_gem_remove_in_second_i
 ldy #1
 lda (@heap_ptr),y

 cmp @gem_remove_in_second
 beq ?gem0_removed

 cmp @gem_remove_in_second+1
 beq ?gem1_removed

 cmp @gem_remove_in_second+2
 beq ?gem2_removed

 cmp @gem_remove_in_second+3
 beq ?gem3_removed

?already_removed
 ldy #255 ; nichts erscheint
 ldx #255
 rts

?gem0_removed
 lda @gem_removed
 bne ?already_removed

 ldy #0
 ldx #0
 rts

?gem1_removed
 lda @gem_removed+1
 bne ?already_removed
 ldy #1
 ldx #0
 rts

?gem2_removed
 lda @gem_removed+2
 bne ?already_removed
 ldy #2
 ldx #0
 rts

?gem3_removed
 lda @gem_removed+3
 bne ?already_removed
 ldy #3
 ldx #0
 rts
