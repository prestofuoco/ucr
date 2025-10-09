;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 3, ex 4
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================

.ORIG x3000
LD R1, NEWLINE
LEA R2, DATA_PTR

DO_WHILE_IN
    GETC
    OUT
    STR R0, R2, #0
    ADD R2, R2, #1
    ADD R0, R0, x-A
    BRnp DO_WHILE_IN
END_DO_WHILE_IN

ADD R2, R2, #1
STR R1, R2, #0
LEA R2, DATA_PTR

DO_WHILE_OUT
    LDR R0, R2, #0
    OUT
    ADD R0, R0, x-A
    BRz EXIT_OUT
    LD R0, NEWLINE
    OUT
    ADD R2, R2, #1
    BRp DO_WHILE_OUT
END_DO_WHILE_OUT

EXIT_OUT
HALT

;LOCAL DATA
DEC_10      .FILL   #10
NEWLINE     .FILL   xA
DATA_PTR    .FILL   x4000

.END