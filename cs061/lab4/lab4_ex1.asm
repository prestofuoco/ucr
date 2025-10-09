;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 4, ex 1
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================
.ORIG x3000
AND R0, R0, #0
LD R1, MEMORY_LOCATION
LD R5, SUB_FILL_ARRAY_3200
JSRR R5
HALT

;LOCAL DATA
MEMORY_LOCATION         .FILL   x4000
SUB_FILL_ARRAY_3200     .FILL   x3200
.END

;------------------------------------------------------------------------
; Subroutine: SUB_FILL_ARRAY_3200
; Parameter (R1): The starting address of the array. This should be
; unchanged at the end of the subroutine!
; Postcondition: The array has values from 0 through 9.
; Return Value (None)
;-------------------------------------------------------------------------
.ORIG x3200
AND R2, R2, #0
ADD R4, R1, #0

DO_WHILE_LOOP
STR R2, R4, #0
ADD R4, R4, #1
ADD R2, R2, #1
ADD R3, R2, #-10
BRn DO_WHILE_LOOP
END_DO_WHILE_LOOP

HALT
.END

.ORIG x4000
ARRAY   .BLKW   #10
.END