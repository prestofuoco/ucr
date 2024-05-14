;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 3, ex 2
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================

.ORIG x3000
LD R1, DEC_10
LEA R2, ARRAY_1

DO_WHILE
    GETC
    STR R0, R2, #0
    ADD R2, R2, #1
    ADD R1, R1, #-1
    BRp DO_WHILE
END_DO_WHILE

HALT

;LOCAL DATA
ARRAY_1     .BLKW   #10
DEC_10      .FILL   #10

.END