; -*- text -*-
;
; OXYGENE#2 Simple 64K
;
; Wir bauen den ganzen VBI nach
;

; THIS FILE WILL INCLUDE BY OTHER FILE
;

 .local

;NMIEN=$D40E ; 54286
; 128 = dli
; 64 = vbi

;NMIRES=$D40F ; 54287 write
;NMIST=$D40F  ; 54287  read

?VDSLST= $200
?VVBLKI= $222
?VIMIRQ= $216 ; Zeigt nach $c030

; PORTB=$D301


; Initialisiert das RAM unter dem OS
; 1. Interrupts stoppen,
; 2. RAM unter OS aktivieren
; 3. Alle wichtigen Pointer in diese Routinen verbiegen
; 4. Interrupts wieder aktivieren
;
; einmaliges INC 54017 aktiviert ROM, wenn RAM aktiv war
; einmaliges DEC 54017 aktiviert RAM, wenn ROM aktiv war
;
@INIT_SIMPLE_64K
 SEI                 ; Stop all IRQs
 LDA #0
 STA NMIEN          ; keine Interrupts mehr zulassen

 JSR @ACTIVATE_RAM
 JSR ?SET_POINTER_FFFA

; Start VBI only.
; Solange DLI (VDSLST) nicht gesetzt ist, ist es gefaehrlich, sonst koennte ein DLI im RAM landen.
 LDA #~01000000
 STA NMIEN ; alle Interrupts wieder zulassen
 CLI

 RTS

; lange Routinen, um das RAM einzuschalten
; dafuer klappt es aber immer! Auch wenn RAM schon aktiv ist
@ACTIVATE_RAM
 LDA PORTB
 AND #~11111100
 ORA #~00000010 ; bit 0==0 OS-RAM bit 1==1 BASIC-RAM
 STA PORTB
 RTS


; lange Routinen, um das ROM einzuschalten
; dafuer klappt es aber immer! Auch wenn ROM schon aktiv ist
@ACTIVATE_ROM
 LDA PORTB
 AND #~11111100
 ORA #~00000011 ; bit 0==1 OS-ROM bit 1==1 BASIC-RAM
 STA PORTB
 RTS

; die Zeiger $FFFA,2 ist fuer den NMI (VBI & DLI) Interrupt
; $FFFC fuer Reset
; $FFFE fuer Maskable Interrupts (Tastatur, ...)
?SET_POINTER_FFFA
 LDX #0
?POINTER_LOOP
 LDA ?NEWPOINTER,X
 STA $FFFA,X
 INX
 CPX #6
 BNE ?POINTER_LOOP
 RTS

?NEWPOINTER
 .word ?NEW_NONE_MASKABLE_IRQ ; $c018
 .word 0                      ; ist mir humpe
 .word ?NEW_MASKABLE_IRQ      ; $c02c

; extract from TurboBasic
; Voll cool gemacht, Wenn ein Interrupt auftritt,
; wird einfach das OS-ROM aktiviert und in den Standard OS Interrupt
; gesprungen
;
; None Maskable Interrupt
; Der Maskable Interrupt macht es genauso, OS-ROM aktivieren
; und die Standard OS Routinen anspringen

?RETURN_FROM_OS_IRQ
         DEC PORTB ; OS RAM    ;    24A6: CE 01 D3

@insert_music_routine_here
;         jsr @music_vbi_with_OS_RAM
 nop
 nop
 nop

         PLA                    ;    24A4: 68
         TAX                    ;    24A5: AA
         PLA                    ;    24A9: 68
         RTI                    ;    24AA: 40
;-------------------------------; -------------------
?RETURN_FROM_OS_MASKABLE_IRQ
         DEC PORTB ; OS RAM    ;    24A6: CE 01 D3
         PLA                    ;    24A9: 68
         RTI                    ;    24AA: 40

;-------------------------------; -------------------
?NEW_NONE_MASKABLE_IRQ
L24AB    BIT NMIST             ;    24AB: 2C 0F D4
         BPL L24B3              ;    24AE: 10 03
         JMP (?VDSLST)          ;    24B0: 6C 00 02
;-------------------------------; -------------------
L24B3    PHA                    ;    24B3: 48
         TXA                    ;    24B4: 8A
         PHA                    ;    24B5: 48
         LDA #>?RETURN_FROM_OS_IRQ ; 24B6: A9 24
         PHA                    ;    24B8: 48
         LDA #<?RETURN_FROM_OS_IRQ ; 24B9: A9 A4
         PHA                    ;    24BB: 48
         TSX                    ;    24BC: BA
         LDA $0105,X            ;    24BD: BD 05 01
         PHA                    ;    24C0: 48
         CLD                    ;    24C1: D8
         PHA                    ;    24C2: 48
         TXA                    ;    24C3: 8A
         PHA                    ;    24C4: 48
         TYA                    ;    24C5: 98
         PHA                    ;    24C6: 48
         INC PORTB ; OS ROM    ;    24C7: EE 01 D3
         STA NMIRES            ;    24CA: 8D 0F D4
         JMP (?VVBLKI)          ;    24CD: 6C 22 02
;-------------------------------; -------------------
?NEW_MASKABLE_IRQ
L24D0    PHA                    ;    24D0: 48
         LDA #>?RETURN_FROM_OS_MASKABLE_IRQ ; 24D1: A9 24
         PHA                    ;    24D3: 48
         LDA #<?RETURN_FROM_OS_MASKABLE_IRQ ; 24D4: A9 A6
         PHA                    ;    24D6: 48
         PHP                    ;    24D7: 08
         INC PORTB             ;    24D8: EE 01 D3
         JMP (?VIMIRQ)          ;    24DB: 6C 16 02
