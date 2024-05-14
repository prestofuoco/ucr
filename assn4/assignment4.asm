;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Assignment name: Assignment 4
; Lab section: 023
; TA: Cody Kurpanek
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
;THE BINARY REPRESENTATION OF THE USER-ENTERED DECIMAL NUMBER MUST BE STORED IN R4
;=================================================================================

.ORIG x3000		
;-------------
;Instructions
;-------------
BEGIN
; output intro prompt
LD R0, introPromptPtr
PUTS

; Set up flags, counters, accumulators as needed
AND R1, R1, #0          ;SIGN FLAG
AND R2, R2, #0
AND R3, R3, #0
AND R4, R4, #0          ;binary result
AND R6, R6, #0
ADD R6, R6, #5
AND R7, R7, #0

GET_CHAR_LOOP
    ; Get first character, test for '\n', '+', '-', digit/non-digit 	
    GETC
    OUT
    
    ; is very first character = '\n'? if so, just quit (no message)!
    newlineCase
    ADD R3, R0, x-A
    BRnp posCase
    ADD R3, R6, #-5
    BRnp NEG_CHECK
    HALT
    
    ; is it = '+'? if so, ignore it, go get digits
    posCase
    LD R5, posSign
    ADD R3, R0, R5
    BRnp negCase
    AND R1, R1, #0
    BRnzp GET_CHAR_LOOP
    
    ; is it = '-'? if so, set neg flag, go get digits
    negCase
    LD R5, negSign
    ADD R3, R0, R5
    BRnp getZero
    ADD R1, R1, #1      ;use r1 as neg flag
    BRnzp GET_CHAR_LOOP
    
    ; is it < '0'? if so, it is not a digit	- o/p error message, start over
    getZero
    LD R5, ZERO
    ADD R3, R0, R5
    BRzp getNine
    LD R0, errorMessagePtr      ;error message
    PUTS
    BRnzp BEGIN
    
    ; is it > '9'? if so, it is not a digit	- o/p error message, start over
    getNine
    LD R5, NINE
    ADD R3, R0, R5
    BRnz CONVERSION
    LD R0, errorMessagePtr      ;error message
    PUTS
    BRnzp BEGIN
    
    ; if none of the above, first character is first numeric digit - convert it to number & store in target register!
    CONVERSION
    LD R5, ZERO
    ADD R0, R0, R5
    ;convert to binary here
    ADD R2, R2, #9
    AND R7, R7, #0
    ADD R7, R4, #0
    MULT_LOOP
    ADD R7, R7, R4
    ADD R2, R2, #-1
    BRp MULT_LOOP
    ADD R4, R7, R0

    ; Now get remaining digits from user in a loop (max 5), testing each to see if it is a digit, and build up number in accumulator
    ADD R6, R6, #-1
    BRp GET_CHAR_LOOP

; remember to end with a newline!
END_PROGRAM
LD R0, NEWLINE
OUT

NEG_CHECK
    ADD R1, R1, #0
    BRz SKIPNEG
    NOT R4, R4
    ADD R4, R4, #1

SKIPNEG
HALT

;---------------	
; Program Data
;---------------

introPromptPtr  .FILL xB000
errorMessagePtr .FILL xB200
arrayPtr        .FILL xB400
posSign         .FILL x-2B
negSign         .FILL x-2D
ZERO            .FILL x-30
NINE            .FILL x-39
NEWLINE         .FILL xA

.END

;------------
; Remote data
;------------
.ORIG xB000	 ; intro prompt
.STRINGZ	 "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"

.END					

.ORIG xB200	 ; error message
.STRINGZ	 "ERROR: invalid input\n"

.END

.ORIG xB400     ;number array
.BLKW       #6

;---------------
; END of PROGRAM
;---------------
.END

;-------------------
; PURPOSE of PROGRAM
;-------------------
; Convert a sequence of up to 5 user-entered ascii numeric digits into a 16-bit two's complement binary representation of the number.
; if the input sequence is less than 5 digits, it will be user-terminated with a newline (ENTER).
; Otherwise, the program will emit its own newline after 5 input digits.
; The program must end with a *single* newline, entered either by the user (< 5 digits), or by the program (5 digits)
; Input validation is performed on the individual characters as they are input, but not on the magnitude of the number.
