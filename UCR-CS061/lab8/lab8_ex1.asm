;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 8, ex 1
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================

.orig x3000

LD R6, top_stack_addr

LD R5, LOAD_FILL
JSRR R5
LD R5, OUTPUT_DEC
JSRR R5

; Test harness
;-------------------------------------------------

HALT

; Test harness local data
;-------------------------------------------------
top_stack_addr  .fill xFE00
LOAD_FILL       .FILL x3200
OUTPUT_DEC      .FILL x3400

.end

;=================================================
; Subroutine: LOAD_FILL_VALUE_3200
; Parameter: // Fixme
; Postcondition: // Fixme
; Return Value: // R2
;=================================================

.orig x3200
; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0

; Code
LD R1, VAL1

; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1
RET

;LOCAL DATA
VAL1    .FILL   #32760
.end

;=================================================
; Subroutine: OUTPUT_AS_DECIMAL_3400
; Parameter: // R1
; Postcondition: // Fixme
; Return Value: // Fixme
;=================================================

.orig x3400
; Backup registers
ADD R6, R6, #-1
STR R7, R6, #0

; Code
AND R2, R2, #0      ;checker
AND R3, R3, #0      ;counter

LD R0, MSB_1
ADD R2, R1, #0
AND R2, R2, R0
BRZ SKIP_CONVERSION

CONVERT_POS
    NOT R1, R1
    ADD R1, R1, #1      ;convert to +
    
LD R0, MINUS
OUT

SKIP_CONVERSION

; CODE
LD R2, DEC_10000
DO_WHILE_10000
    ADD R1, R1, R2
    BRN END_DO_WHILE_10000
    ADD R3, R3, #1
    BRnzp DO_WHILE_10000
END_DO_WHILE_10000

NOT R2, R2
ADD R2, R2, #1      ;+ check for add
ADD R1, R1, R2

ADD R3, R3, #0
BRz SKIP_TO_1000

LD R0, ASCII
ADD R0, R3, R0
OUT

SKIP_TO_1000

AND R3, R3, #0
LD R2, DEC_1000
DO_WHILE_1000
    ADD R1, R1, R2
    BRn END_DO_WHILE_1000
    ADD R3, R3, #1
    BRnzp DO_WHILE_1000
END_DO_WHILE_1000

NOT R2, R2
ADD R2, R2, #1
ADD R1, R1, R2

ADD R3, R3, #0
BRz SKIP_TO_100

LD R0, ASCII
ADD R0, R3, R0
OUT

SKIP_TO_100

AND R3, R3, #0
LD R2, DEC_100
DO_WHILE_100
    ADD R1, R1, R2
    BRn END_DO_WHILE_100
    ADD R3, R3, #1
    BRnzp DO_WHILE_100
END_DO_WHILE_100

NOT R2, R2
ADD R2, R2, #1
ADD R1, R1, R2

ADD R3, R3, #0
BRz SKIP_TO_10

LD R0, ASCII
ADD R0, R3, R0
OUT

SKIP_TO_10

AND R3, R3, #0
LD R2, DEC_10
DO_WHILE_10
    ADD R1, R1, R2
    BRn END_DO_WHILE_10
    ADD R3, R3, #1
    BRnzp DO_WHILE_10
END_DO_WHILE_10

NOT R2, R2
ADD R2, R2, #1
ADD R1, R1, R2

ADD R3, R3, #0
BRz END_CHECK

LD R0, ASCII
ADD R0, R3, R0
OUT

END_CHECK

LD R0, ASCII
ADD R0, R1, R0
OUT

; Restore registers
LDR R7, R6, #0
ADD R6, R6, #1
RET

;LOCAL DATA
MSB_1           .FILL #-32768
ASCII           .FILL x30
DEC_10000       .FILL #-10000
DEC_1000        .FILL #-1000
DEC_100         .FILL #-100
DEC_10          .FILL #-10
MINUS           .FILL #45

.end