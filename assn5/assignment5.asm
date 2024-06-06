; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Assignment name: Assignment 5
; Lab section: 023
; TA: Cody Kurpanek
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=================================================================================
; PUT ALL YOUR CODE AFTER THE main LABEL
;=================================================================================

;---------------------------------------------------------------------------------
;  Initialize program by setting stack pointer and calling main subroutine
;---------------------------------------------------------------------------------
.ORIG x3000

; initialize the stack
ld r6, stack_addr

; call main subroutine
lea r5, main
jsrr r5

;---------------------------------------------------------------------------------
; Main Subroutine
;---------------------------------------------------------------------------------
main
; get a string from the user
LD R1, user_prompt_ptr
LEA R2, user_string
LD R5, get_user_string_addr
JSRR R5

; find size of input string
LEA R1, user_string
LD R5, strlen_addr
JSRR R5

; call palindrome method
ADD R2, R1, R4
ADD R2, R2, #-1
LD R5, palindrome_addr
JSRR R5

; determine if string is a palindrome
ADD R2, R0, #0

; print the result to the screen
LD R0, result_string_ptr
PUTS

; decide whether or not to print "not"
ADD R2, R2, #0
BRp OUTPUT_FINAL_STRING

LD R0, not_string_ptr
PUTS

OUTPUT_FINAL_STRING
LD R0, final_string_ptr
PUTS

HALT

;---------------------------------------------------------------------------------
; Required labels/addresses
;---------------------------------------------------------------------------------

; Stack address ** DO NOT CHANGE **
stack_addr           .FILL xFE00

; Addresses of subroutines, other than main
get_user_string_addr    .FILL x3200
strlen_addr             .FILL x3300
palindrome_addr         .FILL x3400

; Reserve memory for strings in the program
user_prompt_ptr     .FILL xB100
result_string_ptr   .FILL xB200
not_string_ptr      .FILL xB300
final_string_ptr    .FILL xB400

; Reserve memory for user input string
user_string         .BLKW #100

.END

;---------------------------------------------------------------------------------
; get_user_string - get string from console
;
; parameter: R1 - prompt string
; parameter: R2 - address of string
;---------------------------------------------------------------------------------
.ORIG x3200
get_user_string
; Backup all used registers, R7 first, using proper stack discipline
ADD R6, R6, #-1
STR R7, R6, #0

ADD R0, R1, #0
PUTS

GET_STR_LOOP
    GETC
    OUT
    
    ADD R3, R0, x-A
    BRz END_GET_STR
    STR R0, R2, #0
    ADD R2, R2, #1
    BRnzp GET_STR_LOOP
END_GET_STR

AND R0, R0, #0
LDR R0, R2, #0

; Resture all used registers, R7 last, using proper stack discipline
LDR R7, R6, #0
ADD R6, R6, #1
RET
.END

;---------------------------------------------------------------------------------
; strlen - compute the length of a zero terminated string
;
; parameter: R1 - the address of a zero terminated string
;
; returns: R4 - the length of the string
;---------------------------------------------------------------------------------
.ORIG x3300
strlen
; Backup all used registers, R7 first, using proper stack discipline
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0

AND R0, R0, #0      ;using r0 as counter
BEGIN_COUNT
    LDR R0, R1, #0
    ADD R0, R0, #0
    BRz END_COUNT
    ADD R4, R4, #1
    ADD R1, R1, #1
    BRnzp BEGIN_COUNT
END_COUNT

; Restore all used registers, R7 last, using proper stack discipline
LDR R1, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1
RET
.END

;---------------------------------------------------------------------------------
; palindrome - check if inputted string is a palindrome
;
; parameter: R1 - the address of a zero terminated string
; parameter: R2 - the address of the last character in string
;
; returns: R0 - true (1) if palindrome, false (0) if not palindrome
;---------------------------------------------------------------------------------
.ORIG x3400
palindrome ; Hint, do not change this label and use for recursive calls
; Backup all used registers, R7 first, using proper stack discipline
ADD R6, R6, #-1
STR R7, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0

ADD R3, R2, #0          ;check if addresses are the same
NOT R3, R3
ADD R3, R3, #1
ADD R3, R3, R1
BRzp RESULT_TRUE

LDR R3, R1, #0          ;load r3 and r4 with characters
LDR R4, R2, #0
NOT R4, R4              ;prepare for comparison, make r4 negative
ADD R4, R4, #1
ADD R5, R3, R4          ;check if pair
BRnp RESULT_FALSE

ADD R1, R1, #1          ;move to next addresses to compare
ADD R2, R2, #-1

JSR PALINDROME          ;recursion
ADD R5, R0, #0
BRz END_PALINDROME

RESULT_TRUE
AND R0, R0, #0
ADD R0, R0, #1
BRnzp END_PALINDROME

RESULT_FALSE
AND R0, R0, #0

END_PALINDROME
; Restore all used registers, R7 last, using proper stack discipline
LDR R1, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R7, R6, #0
ADD R6, R6, #1
RET
.END

;---------------------------------------------------------------------------------
;REMOTE DATA
.ORIG xB100
user_prompt         .STRINGZ "Enter a string: "
.END

.ORIG xB200
result_string       .STRINGZ "The string is "
.END

.ORIG xB300
not_string          .STRINGZ "not "
.END

.ORIG xB400
final_string        .STRINGZ "a palindrome\n"
.END