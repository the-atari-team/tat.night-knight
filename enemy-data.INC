;; -*- text -*-
;
; Night Knight enemy data
;

; space for enemy data
@enemy_xpos
 .DC MAX_ENEMIES 0

@enemy_ypos
 .DC MAX_ENEMIES 0

@enemy_xstep
 .DC MAX_ENEMIES 0

@enemy_ystep
 .DC MAX_ENEMIES 0

@enemy_direction
 .DC MAX_ENEMIES 0

@enemy_types
 .DC MAX_ENEMIES 0

@enemy_color
 .DC MAX_ENEMIES 0

@enemy_is_jump
 .DC MAX_ENEMIES 0

@enemy_is_jump_up
 .DC MAX_ENEMIES 0

@enemy_jump_animation
 .DC MAX_ENEMIES 0

@enemy_waitforani
 .DC MAX_ENEMIES 0

@enemy_waitforani_walk_init
 .byte 0

@enemy_anim_number
 .DC MAX_ENEMIES 0

@enemy_anim_waitfor
 .DC MAX_ENEMIES 0

@enemy_user_data
 .DC MAX_ENEMIES 0

@arrow_in_move
 .DC MAX_ENEMIES 0

@attack_index
 .DC MAX_ENEMIES 0

;; byte arrays
;@enemy_to_draw_old
; .DC MAX_ENEMIES 0
;
;@enemy_to_draw_new
; .DC MAX_ENEMIES 0
; TODO: Jumptable anpassen, das nicht zuu gleichmaessig gesprungen wird
@jump_table
; .byte -4,-4,-4,-4,-4,-4,-4,-4,0,0   ; jump up
;
; .byte  4,4,4,4,4,4,4,4              ; jump down
; .byte  4,4,4,4,4,4,4,4,4,4
; .byte  4,4,4,4,4,4,4,4,4,4
; .byte  4,4,4,4,4,4,4,4,4,4,4,4
; .byte  127                          ; end mark

 .byte -6,-6,-4,-4,-4,-4,-4,-2,-2,0

 .byte  2,2,4,4,4,4,4,4,4
 .byte  4,4,4,4,4,4,4,4,4,4
 .byte  4,4,4,4,4,4,4,4,4,4
 .byte  4,4,4,4,4,4,4,4,4,4,4,4
 .byte  127                          ; end mark
; .byte 6,6,6,6,6,6,6,6,6,6
; .byte 6,6,6,6,6,6,6,6,6,6
; .byte 6,6,6,6,6,6,6,6
; .byte 127


@wizard_can_change_the_floor
 .byte 0

; usage: @getEnemyToRight(type, animation_number)
; returns the number to show animation data
; expect word array @enemy_to_right[12] = [...] anywhere in the code
@getEnemyToRight
@getEnemyToRight_II
 ldy #1
 lda (@heap_ptr),y ; type
 tay

 lda @enemy_to_right_low,y
 sta @REG
 lda @enemy_to_right_high,y
 sta @REG+1

?getEnemyToLeftOrRight
 ldy #3
 lda (@heap_ptr),y ; animation number
 tay
 lda (@REG),y
 tay
 ldx #0
 rts

; usage: @getEnemyToLeft(type, animation_number)
; expect word array @enemy_to_left[12] = [...] anywhere in the code
@getEnemyToLeft
@getEnemyToLeft_II
 ldy #1
 lda (@heap_ptr),y ; type
 tay

 lda @enemy_to_left_low,y
 sta @REG
 lda @enemy_to_left_high,y
 sta @REG+1

 jmp ?getEnemyToLeftOrRight
