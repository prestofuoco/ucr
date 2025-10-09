;=========================================================================
; Name & Email must be EXACTLY as in Gradescope roster!
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Assignment name: Assignment 3
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
LD R6, Value_ptr		; R6 <-- pointer to value to be displayed as binary
LDR R1, R6, #0			; R1 <-- value to be displayed as binary 
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
LD R2, DEC_4

OUTER_LOOP
    LD R3, DEC_4
    
    INNER_LOOP
        LD R0, ZERO         ; load zero in ascii
        LD R4, HEX_8K       ; loads value to AND against R1 for bit value
        AND R4, R4, R1      ; check MSB and print corresponding from leading bit
        BRn PRINT_ONE       ; skips to 1 if negative. otherwise prints 0 and skips to end of loop
        
        PRINT_ZERO
            OUT
            BRnzp END_PRINT
        
        PRINT_ONE
            ADD R0, R0, #1
            OUT
            
        END_PRINT
        
        ADD R1, R1, R1      ; moves to next bit (left shift)
        ADD R3, R3, #-1     ; decrement loop counter and if 0 checks if end of either whole thing or 4 bits
        BRp INNER_LOOP      ; if neither goes back to print loop
            
    END_INNER_LOOP
    
    ADD R2, R2, #-1         ; adds a newline after fully printed
    BRz NEWLINE_OUT
    
    LD R0, SPACE            ; prints a space every 4 bits
    OUT
    BRnzp OUTER_LOOP

END_OUTER_LOOP

NEWLINE_OUT
    LD R0, NEWLINE
    OUT

HALT
;---------------	
;Data
;---------------
Value_ptr	.FILL   xCA01	; The address where value to be displayed is stored
ZERO        .FILL   x30     ; 0... you get the idea
SPACE       .FILL   x20     ; space in ascii
NEWLINE     .FILL   xA      ; newline in ascii
HEX_8K      .FILL   x8000   ; this is to check leading bit
DEC_4       .FILL   #4      ; for loops or whateva
.END

.ORIG xCA01					; Remote data
Value .FILL xABCD			; <----!!!NUMBER TO BE DISPLAYED AS BINARY!!! Note: label is redundant.
;---------------	
;END of PROGRAM
;---------------	
.END
