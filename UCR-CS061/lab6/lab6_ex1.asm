;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 5, ex 1
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================
.orig x3000
; Initialize the stack. Don't worry about what that means for now.
ld r6, top_stack_addr ; DO NOT MODIFY, AND DON'T USE R6, OTHER THAN FOR BACKUP/RESTORE

; your code goes here
LEA R1, CHAR_ARRAY
LD R2, SUB_GET_STRING
JSRR R2
halt

; your local data goes here
SUB_GET_STRING  .fill x3200
CHAR_ARRAY      .BLKW #100
top_stack_addr  .fill xFE00 ; DO NOT MODIFY THIS LINE OF CODE
.end

; your subroutines go below here

;------------------------------------------------------------------------
; Subroutine: SUB_GET_STRING_3200
; Parameter (R1): The starting address of the character array
; Postcondition: The subroutine has prompted the user to input a string,
;	terminated by the [ENTER] key (the "sentinel"), and has stored 
;	the received characters in an array of characters starting at (R1).
;	the array is NULL-terminated; the sentinel character is NOT stored.
; Return Value (R5): The number of non-sentinel chars read from the user.
;	R1 contains the starting address of the array unchanged.
;-------------------------------------------------------------------------
.ORIG x3200
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0

AND R5, R5, #0

GET_CHAR
GETC
OUT
ADD R0, R0, x-A     ;check for sentinel value
BRz END_GET_CHAR    ;exit if sentinel value

ADD R0, R0, xA      ;restore r0 to pre-check
STR R0, R1, #0      ;store values in r1
ADD R5, R5, #1
ADD R1, R1, #1
BRnzp GET_CHAR      ;loop unconditionally
END_GET_CHAR

LDR R1, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1
RET
.END