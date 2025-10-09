;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Assignment name: Assignment 2
; Lab section: 023
; TA: Cody Kurpanek
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team
; (apart from what was provided in the starter file).
;
;=========================================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------

;----------------------------------------------
;output prompt
;----------------------------------------------	
LEA R0, intro			; get starting address of prompt string
PUTS			    	; Invokes BIOS routine to output string

;-------------------------------
;INSERT YOUR CODE here
;--------------------------------

AND R1, R1, #0  ;assign registers
AND R2, R2, #0
LD R4, tonum
LD R5, toascii

GETC    ;get and output first value from console
OUT
ADD R1, R0, #0
LD R0, newline ;output newline
OUT

GETC    ;get and ouput second value from console
OUT
ADD R2, R0, #0
LD R0, newline  ;output newline
OUT

ADD R0, R1, #0  ;output first num
OUT
LEA R0, subtr   ;output subtract sign
PUTS
ADD R0, R2, #0  ;output second num
OUT
LEA R0, equal   ;output equals sign
PUTS

ADD R1, R1, R4  ;convert R1 to decimal
ADD R2, R2, R4  ;convert R2 to decimal

BRz OUTPUT_RESULT

SUBTR_LOOP   ;perform subtraction
    ADD R1, R1, #-1
    ADD R2, R2, #-1
    BRp SUBTR_LOOP
END_SUBTR_LOOP

ADD R1, R1, #0
BRn MAKE_POSITIVE
BRzp OUTPUT_RESULT

MAKE_POSITIVE   ;make result positive if negative
    LD R0, negat
    OUT
    NOT R1, R1
    ADD R1, R1, #1

OUTPUT_RESULT   ;outputs result
    ADD R0, R1, R5  ;convert result to ascii and load to R0
    OUT

LD R0, newline
OUT

HALT				; Stop execution of program
;------	
;Data
;------
; String to prompt user. Note: already includes terminating newline!
intro 	.STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 		; prompt string - use with LEA, followed by PUTS.
newline .FILL       x0A	; newline character - use with LD followed by OUT
subtr   .STRINGZ    " - "
equal   .STRINGZ    " = "
negat   .FILL       x2D
tonum   .FILL       x-30
toascii .FILL       x30

;---------------	
;END of PROGRAM
;---------------	
.END

