;=================================================
; Name: Andre Winkel
; Email: awink002@ucr.edu
; 
; Lab: lab 1, ex 0
; Lab section: 023
; TA: Cody Kurpanek
; 
;=================================================

.ORIG x3000
    ;INSTRUCTIONS
    LEA R0, MSG_TO_PRINT
    PUTS
    HALT
    
    ;LOCAL DATA
    MSG_TO_PRINT .STRINGZ "Hello world!\n"
.END