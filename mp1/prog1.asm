;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; R0 is letter which will be printed
; R1 is digit counter
; R2 is bit counter
; R3 is print counter
; R4 is ascii value of letter being printed
; R5 is hex value of letter being printed 
; R6 is address of letter being printed

; Initializing registers

	AND R3, R3, #0		; Initializes print counter
	AND R6, R6, #0		; Initializes address of letter
	AND R4, R4, #0		; Initializes ascii value of letter
	LD R6, HIST_ADDR	; Load R6 with histogram starting address
	ADD R6, R6, #-1		
	ADD R3, R3, #-15
	ADD R3, R3, #-12	

PRINTLOOP	
	ADD R3, R3, #27		; Add 27 to print counter every loop
	ADD R4, R4, #31		; Add 64 to R4
	ADD R4, R4, #31
	ADD R4, R4, #2
	AND R0, R0, #0		; Clear R0
	ADD R0, R4, #0		; Make R0 the value of R4
	OUT			; Print out R0 which is R4
	AND R0, R0, #0		; Clear R0
	LD R0, SYMBOL_SPACE	;
	OUT
	ADD R6, R6, #1		; Increments memory address of letter
	LDR R5, R6, #0		; Loads hex value of letter being printed into R5
	AND R1, R1, #0		

DIGITLOOP	
	ADD R1, R1, #-4		; Branch to OUTER if number of digits printed is greater than 3
	BRzp OUTER		
	ADD R1, R1, #4		
	AND R0, R0, #0		
	AND R2, R2, #0		

BITCOUNTER	
	ADD R2, R2, #-4		; Decrease R2 bit counter  by 4
	BRzp PRINTDIGIT		; Print digit if it is not negative
	ADD R2, R2, #4		; Increase R2 bit counter  by 4	
	ADD R0, R0, R0		; Shift R0 left
	ADD R5, R5, #0		; Update hex value of letter
	BRzp ADDZERO		; Branch to ADDZERO if not negative
	ADD R0, R0, #1		; Add 1 to R0 if R3 is negative

ADDZERO		
	ADD R0, R0, #0		; Add 0 to R0 if R3 is zero or positive
	ADD R5, R5, R5		; Multiply R5 by 2 to left shift
	ADD R2, R2, #1		; Add 1 to R2
	BRnzp BITCOUNTER	; Branch back to BITCOUNTER loop

PRINTDIGIT	
	ADD R0, R0, #-9		; Decrease R0 by 9
	BRnz NUMERICAL		; Branch to NUMERICAL if R0 is not positive
	ADD R0, R0, #31		; Increase R0 by 64
	ADD R0, R0, #31
	ADD R0, R0, #2
	BRnzp PRINTLETTER	; Branch to PRINTLETTER

NUMERICAL	
	ADD R0, R0, #31		; Increase R0 by 64
	ADD R0, R0, #31
	ADD R0, R0, #2
		

PRINTLETTER	
	OUT			; Output R0 to monitor
	ADD R1, R1, #1		; Increase digit counter by 1
	BRnzp DIGITLOOP		; Branch back to PRINTLOOP		
		
OUTER				
	ADD R4, R4, #-15	; Reduce R4 by 63
	ADD R4, R4, #-15
	ADD R4, R4, #-15
	ADD R4, R4, #-15
	ADD R4, R4, #-3	
	ADD R3, R3, #1		; Increments print counter
	
LETTERTEST
	ADD R3, R3, #-15	
	ADD R3, R3, #-12
	BRn PRINTLOOP
			BRzp DONE

DONE	HALT			; done

SYMBOL_SPACE	.FILL x20	;Space symbol
NEWLINE		.Fill x0A	;New line

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
