; -*- text -*-
;BASIC-Library
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2020
;

    .LOCAL

; Genau drauf achten, das immer X das hoeherwertige Byte nimmt


; makeword(low, high) macht aus 2 bytes ein Wort.
; return a new word (high * 256 + low)
.if .ref @makeword_ii .or .ref @makeword
@makeword
@makeword_ii
  LDY #3
  LDA (@HEAP_PTR),Y ; high byte Wert holen
  TAX
  LDY #1
  LDA (@HEAP_PTR),Y ; low byte Wert holen
  TAY
  RTS
.endif

; run through INITAD
@start_INITAD
  JMP (738)

; run through RUNAD
@start_RUNAD
  JMP (736)

; Jump into Address, like Basic
.if .ref @usr_i .or .ref @usr
@usr
@usr_i
 LDY #2
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA ?JUMPADR+1
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA ?JUMPADR

 LDA #2
 JSR @ADD_TO_HEAP_PTR

 JSR ?JUMPER

 LDA #2
 JMP @SUB_FROM_HEAP_PTR

?JUMPER
 JMP (?JUMPADR)

?JUMPADR
 .word 0

.endif


; move length Bytes von-adresse, nach-adresse, length
; dabei wird vorwaerts geschoben
; Der Seiteneffekt ist, man setzt in die von-adresse eine 0 und nach-adresse nur ein byte weiter als von-adresse
; jetzt kann unter Angabe der length Speicher geloescht werden.
; eignet sich also nicht um Daten ein Byte nach vorne zu schieben. Das Gegenstueck hierzu heisst @moveup.
;.if .ref @move_iii
@move
@move_iii
; von Adresse
 LDY #1
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+1

; nach Adresse
 LDY #3
 LDA (@HEAP_PTR),Y ; low Wert holen
 STA @REG+2
 INY
 LDA (@HEAP_PTR),Y ; high Wert holen
 STA @REG+3

; length
 LDY #6
 LDA (@HEAP_PTR),Y ; high Wert holen
 TAX             ; oberen Wert merken fuer Auswertung, ob nicht doch move255 genutzt werden kann
 DEY
 LDA (@HEAP_PTR),Y ; low Wert holen

 CPX #0
 BEQ ?MOVE_0TO255_LOOP

; STX @REG+5
 STA @REG+4
 LDY #0

?MOVELOOP_3        ; LOOP for upper 256 Bytes
 LDA (@REG),Y
 STA (@REG+2),Y
 INY
 LDA (@REG),Y      ; unrool brings ~2.3%
 STA (@REG+2),Y
 INY
 BNE ?MOVELOOP_3

 INC @REG+1
 INC @REG+3

; DEC @REG+5
 DEX
 BNE ?MOVELOOP_3

 LDA @REG+4  ; last Bytes

; JMP ?MOVE_0_TO_255_LOOP

?MOVE_0TO255_LOOP
 CMP #0            ; nicht entfernen!
 BEQ ?MOVEEND

; switch to a unrool version, which is up to ~8% faster
; TAX
 LDY #0

 LSR A           ; Anzahl Bytes die kopiert werden sollen /2 (wenn jetzt ungerade ist carry 1)
 TAX
 BCC ?MOVELOOP

 LDA (@REG),Y    ; ein Byte kopieren, falls wir ungerade sind
 STA (@REG+2),Y
 INY
; DEX
 CPX #0          ; X == 0? wir sollten nur 1 byte kopieren
 BEQ ?MOVEEND

?MOVELOOP        ; loop jetzt immer gleich 2 Bytes, dadurch sparen wir pro durchlauf ~3.5Zyklen
 LDA (@REG),Y
 STA (@REG+2),Y
 INY
; DEX
 LDA (@REG),Y
 STA (@REG+2),Y
 INY
 DEX
 BNE ?MOVELOOP

?MOVEEND
 RTS
;.endif

; wartet bis nte Zeile erreicht ist, ggf. ueber die Austastluecke hinaus.
; Ein vsync ist somit nicht noetig, wenn die naechste Abfrage nur 2 Zeilen (228 Takte) spaeter erfolgt
;
; Routine eignet sich sehr gut um Flackern zu verhindert, ein @waitline(100) wartet meist, bis fast die letzte Zeile des
; sichtbaren Bereiches erreicht ist.

;.if .ref @waitline_i
@waitline
@waitline_i
 LDY #1

 LDA VCOUNT         ; aktuelle Zeile
 CMP (@HEAP_PTR),Y
 BEQ ?NO_WAIT_NEED  ; --> same line
 BMI ?WAITLOOP2     ; --> nur warten auf die richtige Zeile

; wir sind aktuell unter der geforderten Linie
; also warten wir erstmal bis wir wieder ueber der gewuenschten Zeile sind
; Wir nutzen dabei nicht peek(20) weil das selbst gestoppt werden kann
; wir nutzen nicht direkt vcount==0 weil das durch ueberlange VBIs verhindert
; werden koennte.
?WAITLOOP1
 LDA VCOUNT
; sta w sync        ; wir halten die CPU immer bis zur naechste Zeile an
?LASTLINE
 cmp (@heap_ptr),y
 BPL ?WAITLOOP1

; Das eigentliche Warten auf die richtige Zeile
?WAITLOOP2
 LDA VCOUNT
; sta w sync        ; wir halten die CPU immer bis zur naechste Zeile an
 CMP (@HEAP_PTR),Y
 BMI ?WAITLOOP2

?NO_WAIT_NEED
 TAY
 LDX #0
 RTS
;.endif

; TODO: sleep_lines (wir wissen, wo wir sind und koennten das evtl. anbieten mit VCOUNT!)
; @sleep(low) wartet low * vsync Zeit. (max 255 1/50s) Dazu wird der interne Zeitzaehler (20) verwendet.
; @pause(low) ist das selbe
; @pause(0) wartet nicht!
;.if .ref @sleep_i .or .ref @pause_i
@sleep
@sleep_i
@pause
@pause_i
  LDY #1
  LDA (@HEAP_PTR),Y ; high Wert holen

  BEQ ?pauseexit
  TAY

?outerpauseloop
  LDA RTCLOK+2

?innerpauseloop
  CMP RTCLOK+2
  BEQ ?innerpauseloop

  DEY
  BNE ?outerpauseloop

?pauseexit
  LDA #0
  TAY
  TAX
  RTS
;.endif
