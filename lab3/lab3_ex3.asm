;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 3, ex 3
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================

.ORIG x3000
LD R1, DEC_10
LEA R2, ARRAY_1

DO_WHILE_IN
    GETC
    STR R0, R2, #0
    ADD R2, R2, #1
    ADD R1, R1, #-1
    BRp DO_WHILE_IN
END_DO_WHILE_IN

LD R1, DEC_10
LEA R2, ARRAY_1

DO_WHILE_OUT
    LDR R0, R2, #0
    OUT
    LD R0, NEWLINE
    OUT
    ADD R2, R2, #1
    ADD R1, R1, #-1
    BRp DO_WHILE_OUT
END_DO_WHILE_OUT

HALT

;LOCAL DATA
ARRAY_1     .BLKW   #10
DEC_10      .FILL   #10
NEWLINE     .FILL   x0A

.END