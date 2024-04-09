; for WiNiFe-Compiler
; (cdw) by TAT 2022
;

 .bank
 .set 6,0
; hiermit bauen wir den Encoder und das Playfield
;
; Der encoder steht jetzt dynamisch direkt hinter dem Playfield
;  *=$BD70
; .include "huffman-decode.INC"

  *=$c000
  .include "CASTLFNT.INC"

  *=$C298
  ; Luecken muessen gefuellt werden, sonst klappt es nicht
  .dc $c4b8-$c298 0

; TODO: Hier ist eine Luecke ab $C298 - $C4B7

  *=$C4B8
 .include "LETTER.INC"

  *=$C800 ;  - ~$CA00 ; fuer Graphics 0  (Wir nutzen nur 64 Zeichen)
 .include "TITLEFNT.INC"

  .dc $CB00-$CA00 0

  *=$CB00
  .include "CASTLE.INC"

  *=$CC00 ; - $BBA0 -1 (928 Bytes!) Zeichen 0 - 115
; Enthaelt:
; - Spielfeld
 .include "NIGHTFNT.INC" ; night-knight-font

  .dc $800 0

  *=$D800

; Enthaelt:
; - Die Spielfeld Daten

 .include "COMPRESSED-PLAYFIELDS.INC" ; Die Playfields

; Der Encoder, steht dynamisch hinter dem Playfield
; Um genau zu beschreiben, wo er liegt, lassen wir per atasm
 .include "huffman-decode.INC"

  .if * >= $fffa
    .error "Memory overflow in playfield-data! * must < $fffa"
  .endif


 .bank
 .set 6,0
