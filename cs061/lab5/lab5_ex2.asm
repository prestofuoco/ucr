;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 7, ex 2
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================

; test harness
.orig x3000
    
    ; Setup parameter
    AND R1, R1, #0
    ADD R1, R1, #5
    
    ; Call the factorial sub-routine
    LD R5, FACT_SUB_ADDR
    JSRR R5
    
halt
;-----------------------------------------------------------------------------------------------
; test harness local data:

FACT_SUB_ADDR   .FILL x3200

;===============================================================================================
.end

; subroutines:

;=======================================================================
; Subroutine: SUB_FACT
; Parameter (R1): Starting number for the factorial.
; Postcondition: Take the factorial of the value in R1.
; Return Value (R0): Result of the factorial.
;=======================================================================
.ORIG x3200
;========================
; Subroutine Instructions
;========================
FACT_SUB_START
; Backup Registers
ST R1, BACKUP_R1_3200
ST R2, BACKUP_R2_3200
ST R5, BACKUP_R5_3200
ADD R3, R7, #0

; Subroutine Logic

ADD R1, R1, #-1
BRz BASE_3200 ; Recursive Base Case: if r1 == 0 jump to base case

; Recursive call
JSR FACT_SUB_START

; Setup multiplication parameters
ADD R2, R0, #0 ; Move result of factorial call to R2
ADD R1, R1, #1 ; Use original value of R1

; Perform multiplication
LD R6, MUL_SUB_ADDR_3200
JSRR R6
BR RESTORE_3200 ; Skip the base case

; Handle base case, return 1
BASE_3200
AND R0, R0, #0
ADD R0, R0, #1

; Restore Registers
RESTORE_3200
LD R1, BACKUP_R1_3200
LD R2, BACKUP_R2_3200
LD R5, BACKUP_R5_3200
ADD R7, R3, #0

RET

;========================
; Subroutine Data
;========================
MUL_SUB_ADDR_3200   .FILL x3400

BACKUP_R1_3200  .BLKW #1
BACKUP_R2_3200  .BLKW #1
BACKUP_R5_3200  .BLKW #1
.END

;=======================================================================
; Subroutine: SUB_MULT
; Parameter (R1): First operand.
; Parameter (R2): Second operand.
; Postcondition: Multiply the first operand by the second operand.
; Return Value (R0): Return the product.
;=======================================================================
.ORIG x3400
;========================
; Subroutine Instructions
;========================
; Backup registers
ST R1, BACKUP_R1_3400
ST R2, BACKUP_R2_3400
ADD R3, R7, #0

; Subroutine logic
AND R0, R0, #0

MULT_LOOP_3400
    ADD R0, R0, R1
    ADD R2, R2, #-1
    BRp MULT_LOOP_3400

; Restore registers
LD R1, BACKUP_R1_3400
LD R2, BACKUP_R2_3400
ADD R7, R3, #0

RET

;========================
; Subroutine Data
;========================
BACKUP_R1_3400  .BLKW #1
BACKUP_R2_3400  .BLKW #1
.END