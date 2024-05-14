;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 4, ex 3
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================
.ORIG x3000
AND R0, R0, #0
LD R1, MEMORY_LOCATION

LD R5, SUB_FILL_ARRAY_3200
JSRR R5

LD R6, SUB_CONVERT_ARRAY_3400
JSRR R6

LD R2, SUB_PRINT_ARRAY_3600
JSRR R2
HALT

;LOCAL DATA
MEMORY_LOCATION         .FILL   x4000
SUB_FILL_ARRAY_3200     .FILL   x3200
SUB_CONVERT_ARRAY_3400  .FILL   x3400
SUB_PRINT_ARRAY_3600    .FILL   x3600
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

RET
.END

;------------------------------------------------------------------------
; Subroutine: SUB_CONVERT_ARRAY_3400
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: Each element (number) in the array should be represented as a character. E.g. 0 -> ‘0’
; Return Value (None)
;-------------------------------------------------------------------------
.ORIG x3400
AND R2, R2, #0
ADD R4, R1, #0
LD R5, ASCII_CONVERT

DO_WHILE_LOOP_CONVERT
LDR R6, R4, #0
ADD R6, R6, R5
STR R6, R4, #0
ADD R4, R4, #1
ADD R2, R2, #1
ADD R3, R2, #-10
BRn DO_WHILE_LOOP_CONVERT
END_DO_WHILE_LOOP_CONVERT

RET
;LOCAL DATA
ASCII_CONVERT   .FILL   x30
.END

;------------------------------------------------------------------------
; Subroutine: SUB_PRINT_ARRAY_3600
; Parameter (R1): The starting address of the array. This should be unchanged at the end of the subroutine!
; Postcondition: Each element (character) in the array is printed out to the console.
; Return Value (None)
;-------------------------------------------------------------------------
.ORIG X3600
LD R2, DEC_10
AND R4, R4, #0
ADD R4, R1, #0

PRINT_WHILE
LDR R0, R4, #0
OUT
ADD R4, R4, #1
ADD R2, R2, #-1
BRp PRINT_WHILE
END_PRINT_WHILE

RET
;LOCAL DATA
DEC_10  .FILL   #10
.END

;=================================================
;ARRAY LOCATION
.ORIG x4000
ARRAY   .BLKW   #10
.END