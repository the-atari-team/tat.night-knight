; -*- text -*-
;STICK-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;
;  enthaelt die Funktionen fuer Stick, Strig
;

; liefert aktuellen Wert zum Feuerknopf
;
; if @strig(0) == 0 then gedrueckt
;
; 0=gedrueckt
; 1=nicht gedrueckt
@STRIG
@STRIG_i
  LDY #1
  LDA (@HEAP_PTR),Y ; der 1. Parameter
  AND #~00000001 ; max 2 Strig
  TAY

  LDA 644,Y ; Schatten zu 53264..
  TAY
  LDX #0
  RTS

; liefert den originalen Stick Wert, kann nur mit 2 Sticks arbeiten (Atari XL)
; 15=nicht bewegt und jedes Bit fuer entsprechende Richtung
;
; if @stick(0) == 14 then oben gedrueckt
; if @stick(0) == 11 then rechts gedrueckt
; if @stick(0) == 7 then links gedrueckt
; if @stick(0) == 13 then unten gedrueckt
;
@STICK
@STICK_i
  LDY #1
  LDA (@HEAP_PTR),Y ; der 1. Parameter
  AND #~00000001 ; max 2 Sticks
  TAY

  LDA 632,Y ; Schatten von 54016..
  TAY
  LDX #0
  RTS

; liefert 1, wenn Stick(n) nach oben gedrueckt wird
;
; if @stickup(0) == 1 then oben gedrueckt
;
@STICKUP
@STICKUP_i
  JSR @STICK
  TYA
  AND #~0001
  BEQ ?STICK_MOVED

?STICK_NOT_MOVED
  LDY #0
  LDX #0
  RTS

?STICK_MOVED
  LDY #1
  LDX #0
  RTS

; liefert 1, wenn Stick(n) nach unten gedrueckt wird
;
; if @stickdown(0) == 1 then unten gedrueckt
;
@STICKDOWN
@STICKDOWN_i
  JSR @STICK
  TYA
  AND #~0010
  BEQ ?STICK_MOVED
  BNE ?STICK_NOT_MOVED

; liefert 1, wenn Stick(n) nach links gedrueckt wird
;
; if @stickleft(0) == 1 then left gedrueckt
;
@STICKLEFT
@STICKLEFT_i
  JSR @STICK
  TYA
  AND #~0100
  BEQ ?STICK_MOVED
  BNE ?STICK_NOT_MOVED

; liefert 1, wenn Stick(n) nach rechts gedrueckt wird
;
; if @stickright(0) == 1 then rechts gedrueckt
;
@STICKRIGHT
@STICKRIGHT_i
  JSR @STICK
  TYA
  AND #~1000
  BEQ ?STICK_MOVED
  BNE ?STICK_NOT_MOVED

