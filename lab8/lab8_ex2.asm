;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 8, ex 2
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================

.orig x3000

LD R6, top_stack_addr

; Test harness
;-------------------------------------------------
LEA R0, STARTTXT
PUTS

GETC
OUT

LD R5, SUB_PARITY_CHECK_3600
JSRR R5

AND R2, R2, #0
ADD R2, R0, #0
LD R0, NEWLINE
OUT

LEA R0, OUTTXT
PUTS

AND R0, R0, #0
ADD R0, R2, #0
OUT

LEA R0, OUTTXT2
PUTS

LD R0, ASCII
ADD R0, R0, R3
OUT

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr          .FILL xFE00
STARTTXT                .STRINGZ "Enter a character: "
NEWLINE                 .FILL xA
OUTTXT                  .STRINGZ "The number of 1's in '"
OUTTXT2                 .STRINGZ "' is: "
SUB_PARITY_CHECK_3600   .FILL x3600
ASCII                   .FILL x30
.end

;=================================================
; Subroutine: PARITY_CHECK_3600
; Parameter: // R0
; Postcondition: // Fixme
; Return Value (R3): // Fixme
;=================================================

.orig x3600

; Backup registers
ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R7, R6, #0

; Code
AND R1, R1, #0
ADD R1, R1, #8      ;counter
AND R2, R2, #0
ADD R2, R2, #1
AND R3, R3, #0

LOOP1
    AND R4, R0, R2
    BRp INC
    CONTINUE
    ADD R2, R2, R2
    ADD R1, R1, #-1
    BRp LOOP1
    BRnzp END_LOOP1
    
INC                 ;helper loop to count num of 1
    ADD R3, R3, #1
    BRnzp CONTINUE
    
END_LOOP1

; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1
LDR R0, R6, #0
ADD R6, R6, #1
RET

.end