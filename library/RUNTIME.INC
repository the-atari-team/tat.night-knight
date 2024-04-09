; -*- text -*-

;RUNTIME-Library fuer Night-Knight, abgespeckt vom Balast
;fuer den WiNiFe-Compiler
;cdw by 'The Atari Team' 1989-2022
; licensed under https://creativecommons.org/licenses/by-sa/2.5/[Creative Commons Licenses]
;

  .LOCAL

@BASIC_MAIN
 RTS

@EXIT
@EXIT_i
 jmp $e477 ; if someone calls @exit(), we hard reset the atari, because we killed the DOS also


; function pointer call
; @(fkt)(...)
; Here jump in with a address given in register X,Y (y+256*x)
@FUNCTION_POINTER

; need 3 cycles more, but no extra memory
  TXA ; 2
  PHA ; 3
  TYA ; 2
  PHA ; 3
  PHP ; 3 ; RTI expect
  RTI ; 6

; sub akku from heap_ptr
@SUB_FROM_HEAP_PTR
    STA @REG

    SEC
    LDA @HEAP_PTR
    SBC @REG
    STA @HEAP_PTR
    BCC ?DEC_HEAD_PTR
    RTS

?DEC_HEAD_PTR
    DEC @HEAP_PTR+1
    RTS

;
;    OO              OO     OO                                      OO       OO
;         OOOOOO          OOOOOOO         OOOOOO  OO   OO OOOOOO  OOOOOOO         OOO OO   OOOOO
;  OOOO   OO   OO  OOOO     OO            OO   OO OO   OO OO   OO   OO     OOOO   OOOOOOO OO   OO
;    OO   OO   OO    OO     OO            OO      OO   OO OO   OO   OO       OO   OO O OO OOOOOOO
;    OO   OO   OO    OO     OO            OO      OO   OO OO   OO   OO       OO   OO O OO OO
; OOOOOOO OO   OO OOOOOOO    OOOO         OO       OOOOOO OO   OO    OOOO OOOOOOO OO O OO  OOOOO
;
; INIT-Runtime
; This is the only function, we call to initialise before program starts
; @Parameter: X-Register must contain the Stack Pointer (TSX)
;             Y-Register will be added to the heap-ptr
;                        This is very helpful for Atari-Basic parameters
@INIT_RUNTIME
     STX ?STACKPOINTER

     LDA #<?LAST_BYTE
     STA @HEAP_PTR
     LDX #>?LAST_BYTE
     STX @HEAP_PTR+1

; we set the APPMHI 256bytes after heap ptr
     STA APPMHI
     INX
     STX APPMHI+1

; if BREAKKEY.INC is included, we have such function and can call it.
 .IF .DEF @INIT_BREAKKEY
     jsr @INIT_BREAKKEY
 .ENDIF

; We copy Basic Parameters to our heap and move the Heap-Pointer
     TYA
;    JMP @ADD_TO_HEAP_PTR ; due to move next function, we save 3 bytes

; Add Akku zum Heap_Ptr
@ADD_TO_HEAP_PTR
    CLC                ; 2
    ADC @HEAP_PTR      ; 3
    STA @HEAP_PTR      ; 3
    BCS ?INC_HEAD_PTR2 ; 2
    RTS                ; 6

?INC_HEAD_PTR2
    INC @HEAP_PTR+1    ; 1+5
    RTS                ; 6

?STACKPOINTER
     .byte 0

@ASSERT_FEHLER
     .word 0

?LAST_BYTE
 .byte 0

; Here starts the Heap-Memory.
;     .BYTE "HEAP"

; We must set heap_ptr start to a word equal address.
; We use the cassette-buffer
  * = $400

;@PARAMETERCOUNT
@HEAP_MEMORY
    .byte 0

; @parameter starts one! byte after heap_memory, because from Atari-basic
; the first byte always contains the count of following parameters.
@PARAMETER
    .DS $007b
    .BYTE $de,$ad,$be,$ef

; Here must not stay anything.
