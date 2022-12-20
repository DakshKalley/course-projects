.ORIG x3000

;The main concept of the program is to find the solve a postfix expression using lc3 code. The overarching idea is that
;it that it detects each input character that the user types in and analyzes the expression off of that using a stack.
;If the input character is 0-9, then it calls a NUMBER function which basically pushes the number onto the stack. If the
;Input is an operator, then the subroutine for the respective operator (+-*/^) is called and performed on the top two value
;Of the stack by popping them out into registers. If an '=' is inputted, then it calculates the final result and uses previous
;code from mp1 to pring the ascii valueof what is stored in R5 through multiple loops. Throughout the program, I am looking for
;an invalid input whether it is that thereis not one value left at the end of the equation in the stack, or if a non-accepted key
; is pressed. If that happens then 'Invalid Input' is printed and the program is terminated. Also, if there is underflow at any point
;in the stack, then 'Invalid Program'Prints as well.
;partners: guibord2
 

AND R0, R0, #0          ;Initialize all Registers
AND R1, R1, #0          ;Initialize all Registers
AND R2, R2, #0          ;Initialize all Registers
AND R3, R3, #0          ;Initialize all Registers
AND R4, R4, #0          ;Initialize all Registers
AND R5, R5, #0          ;Initialize all Registers
AND R6, R6, #0          ;Initialize all Registers
AND R7, R7, #0          ;Initialize all Registers


JSR EVALUATE            ;Call the evaluate subroutine
ADD R3, R5, #0          ;Store the output of R5 from Evaluate into R3 for PRINT_HEX
JSR PRINT_HEX           ;Call the PRINT_HEX subroutine
 
HALT                    ;Stop the program
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
;
PRINT_HEX
    ST R0, PRINTHEXSAVER0   ;Store registers for RET
    ST R1, PRINTHEXSAVER1   ;Store registers for RET
    ST R2, PRINTHEXSAVER2   ;Store registers for RET
    ST R3, PRINTHEXSAVER3   ;Store registers for RET
    ST R4, PRINTHEXSAVER4   ;Store registers for RET
    ST R5, PRINTHEXSAVER5   ;Store registers for RET
    ST R6, PRINTHEXSAVER6   ;Store registers for RET
    ST R7, PRINTHEXSAVER7   ;Store registers for RET
 
    AND R5, R5, #0      ;Set R5 to 0
    ADD R5, R5, #4      ; Initialize Middle Loop Counter
 
 MIDDLE_LOOP
    BRnz HEXPRINTED     ;If all 4 ascii values have been printed, Go to the next row
    AND R0, R0, #0      ;Initializing the bit to 0 (what ascii character is being printed)
    AND R6, R6, #0      ;Set R6 to 0 so we can initialize it.
    ADD R6, R6, #4      ;Initialize small loop counter to add 4 bits to R0
 
INNER_LOOP
    BRnz PRINT_CHAR     ;If 4 bits have been moved into R0, go to print character conditional statement
 
    ADD R0, R0, R0      ;Shift ascii value of character being printed to the left to make room for the incoming 1 or 0
    ADD R3, R3, #0      ;Look at R3
 
    BRzp ZERO           ;Check to see if the MSB of R3 is 1
    ADD R0, R0, #1      ;If MSB on R3 is 1, then add 1 to R0
   
ZERO
    ADD R0, R0, #0      ;If MSB on R3 is 0, then add 0 to R0
 
    ADD R3, R3, R3      ;Shift R3 Left
    ADD R6, R6, #-1     ;Decrement Bit Counter (INNER_LOOP Counter)
   
    BRnzp INNER_LOOP    ;Go back to the top of the INNER_LOOP
 
PRINT_CHAR
    ADD R0, R0, #-9     ;Subtract 9 from 0 so that we can see if it is greater than or equal to 9 by checkinig if it is negative or 0
    BRnz DO_NOHTING     ;Check to see if R0 is less than or equal to nine and branch if it is less than 9
    add R0, R0, #9      ;Reset R0
    ADD R0, R0, #15     ;Add 15 to R0
    ADD R0, R0, #15     ;Add 15 to R0 because I can not add 55 all at once
    ADD R0, R0, #15     ;Add 15 to R0 because I can not add 55 all at once
    ADD R0, R0, #10     ;Add 10 to R0 because I can not add 55 all at once
   
    BRnzp CONTINUE      ;Loop out to continue to pring R0
 
DO_NOHTING
    ADD R0, R0, #9      ;Reset R0 to it's original value
    ADD R0, R0, #15     ;Add 15 to R0 because we can not add 48 all at once
    ADD R0, R0, #15     ;Add 15 to R0 because we can not add 48 all at once
    ADD R0, R0, #15     ;Add 15 to R0 because we can not add 48 all at once
    ADD R0, R0, #3      ;Finish adding 48 to R0
 
CONTINUE
    OUT                 ;Print the Ascii character
    ADD R5, R5, #-1     ;Decrement Middle Loop Counter
    BRnzp MIDDLE_LOOP   ;Go back to top of Middle Loop
 
HEXPRINTED
 
    LD R0, PRINTHEXSAVER0   ;Load registers for RET
    LD R1, PRINTHEXSAVER1   ;Load registers for RET
    LD R2, PRINTHEXSAVER2   ;Load registers for RET
    LD R3, PRINTHEXSAVER3   ;Load registers for RET
    LD R4, PRINTHEXSAVER4   ;Load registers for RET
    LD R5, PRINTHEXSAVER5   ;Load registers for RET
    LD R6, PRINTHEXSAVER6   ;Load registers for RET
    LD R7, PRINTHEXSAVER7   ;Load registers for RET
 
    RET                 ;Return to the main program line
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R5 - current numerical output
;
;R1 - Negative of Checker
;R2 - Stack Start
;R6 - Stack Top
EVALUATE        
 
ST R0, EVALSAVER00          ;Store registers for RET
ST R1, EVALSAVER1           ;Store registers for RET
ST R2, EVALSAVER2           ;Store registers for RET
ST R3, EVALSAVER3           ;Store registers for RET
ST R4, EVALSAVER4           ;Store registers for RET
ST R5, EVALSAVER5           ;Store registers for RET
ST R6, EVALSAVER6           ;Store registers for RET
ST R7, EVALSAVER7           ;Store registers for RET
 
BEGINNINGEV                 ;Beginning of the Evaluate Program.
    GETC                    ;Ask for a character without echoing and a prompt
    OUT                     ;Echo the GETC trap
    ST R0, EVALSAVER0       ;Save the value of R0 into
   
    LD R1, NEGEQUAL         ;Load negative value of equal into R1
    ADD R0, R0, R1          ;Subtract equal from input to see if it is zero
    BRz EQUAL               ;if equal is detected, then equal detected
    LD R0, EVALSAVER0       ;Reset R0 back to the original value
 
    LD R1, NEGSPACE         ;Load negative value of space into R1
    ADD R0, R0, R1          ;Subtract input and equal value
    BRz SPACE               ;If value is a space, go to SPACE
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGZERO          ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGONE           ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGTWO           ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGTHREE         ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGFOUR          ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGFIVE          ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
   
    LD R1, NEGSIX           ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGSEVEN         ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGEIGHT         ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGNINE          ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz NUMBER              ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGPLUS          ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz PLUSSPOT            ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGMINUS         ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz MINSPOT             ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGMULT          ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz MULTSPOT            ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGDIV           ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz DIVSPOT             ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    LD R1, NEGEXP           ;Load negative value into register
    ADD R0, R0, R1          ;Subtract R0 and checking value
    BRz EXPSPOT             ;If equal to zero, branch
    LD R0, EVALSAVER0       ;Reload R0
 
    BRnzp INVEXPR           ;It is an invalid expression if none of the cases are hit
 
PLUSSPOT
    JSR POP                 ;Pop
    ADD R4, R0, #0          ;Store the first popped value in R4
    JSR POP                 ;Pop
    ADD R3, R0, #0          ;Store the second popped value in R3
    ADD R5, R5, #0          ;Look at R5
    BRp INVEXPR             ;If R5 is 1, then there is underflow, and pring invalid expression
    JSR PLUS                ;If there is not underflow, then perform the plus subroutine
    JSR PUSH                ;Push
    BRnzp BEGINNINGEV       ;Go to the beginning of evaluate
 
MINSPOT
    JSR POP                 ;Pop
    ADD R4, R0, #0          ;Store the first popped value in R4
    JSR POP                 ;Pop
    ADD R3, R0, #0          ;Store the second popped value in R3
    ADD R5, R5, #0          ;Look at R5
    BRp INVEXPR             ;If R5 is 1, then there is underflow, and pring invalid expression
    JSR MIN                 ;If there is not underflow, then perform the plus subroutine
    JSR PUSH                ;Push
    BRnzp BEGINNINGEV       ;Go to the beginning of evaluate
 
MULTSPOT
    JSR POP                 ;Pop
    ADD R4, R0, #0          ;Store the first popped value in R4
    JSR POP                 ;Pop
    ADD R3, R0, #0          ;Store the second popped value in R3
    ADD R5, R5, #0          ;Look at R5
    BRp INVEXPR             ;If R5 is 1, then there is underflow, and pring invalid expression
    JSR MUL                 ;If there is not underflow, then perform the plus subroutine
    JSR PUSH                ;Push
    BRnzp BEGINNINGEV       ;Go to the beginning of evaluate
 
DIVSPOT
    JSR POP                 ;Pop
    ADD R4, R0, #0          ;Store the first popped value in R4
    JSR POP                 ;Pop
    ADD R3, R0, #0          ;Store the second popped value in R3
    ADD R5, R5, #0          ;Look at R5
    BRp INVEXPR             ;If R5 is 1, then there is underflow, and pring invalid expression
    JSR DIV                 ;If there is not underflow, then perform the plus subroutine
    JSR PUSH                ;Push
    BRnzp BEGINNINGEV       ;Go to the beginning of evaluate
 
EXPSPOT
    JSR POP                 ;Pop
    ADD R4, R0, #0          ;Store the first popped value in R4
    JSR POP                 ;Pop
    ADD R3, R0, #0          ;Store the second popped value in R3
    ADD R5, R5, #0          ;Look at R5
    BRp INVEXPR             ;If R5 is 1, then there is underflow, and pring invalid expression
    JSR EXP                 ;If there is not underflow, then perform the plus subroutine
    JSR PUSH                ;Push
    BRnzp BEGINNINGEV       ;Go to the beginning of evaluate
 
NUMBER
    LD R0, EVALSAVER0
    ADD R0, R0, #-15        ;Convert number from character hex to actual value
    ADD R0, R0, #-15        ;Convert number from character hex to actual value
    ADD R0, R0, #-15        ;Convert number from character hex to actual value
    ADD R0, R0, #-3         ;Convert number from character hex to actual value
    JSR PUSH                ;Jump to Push subroutine
    BRnzp BEGINNINGEV       ;Go back to the beginning of the evaluate subroutine.
 
SPACE                       ;If space detected,
    BRnzp BEGINNINGEV       ;Goto the beginning of the outer loop
 
EQUAL
    LD R2, STACK_START      ;Load Stack Start into R2
    LD R6, STACK_TOP        ;Load Stack Top into R6
 
    NOT R6, R6              ;Invert R6 to make negative
    ADD R6, R6, #1          ;Find the negative of top
    ADD R2, R2, R6          ;Subtract Start and Top
    ADD R2, R2, #-1         ;Subtract one from the difference and see if it is zero
    BRz EQSOLVED            ;If 0, the equation has been solved
INVEXPR
    LEA R0, INVALID         ;Load the starting address of 'Invalid Expression' to print
    PUTS                    ;Output the string
    LD R0, EVALSAVER00      ;Load registers for RET
    LD R1, EVALSAVER1       ;Load registers for RET
    LD R2, EVALSAVER2       ;Load registers for RET
    LD R3, EVALSAVER3       ;Load registers for RET
    LD R4, EVALSAVER4       ;Load registers for RET
    LD R6, EVALSAVER6       ;Load registers for RET
    LD R7, EVALSAVER7       ;Load registers for RET
    HALT                    ;Stop program
 
EQSOLVED
   
    LDI R5, STACK_START     ;Load the bottom value of the stack into R5 as in the subroutine instructions
    ;ADD R5, R5, #15        ;Restore R5 to character hex value
    ;ADD R5, R5, #15        ;Restore R5 to character hex value
    ;ADD R5, R5, #15        ;Restore R5 to character hex value
    ;ADD R5, R5, #3         ;Restore R5 to character hex value
    LD R0, EVALSAVER00      ;Load registers for RET
    LD R1, EVALSAVER1       ;Load registers for RET
    LD R2, EVALSAVER2       ;Load registers for RET
    LD R3, EVALSAVER3       ;Load registers for RET
    LD R4, EVALSAVER4       ;Load registers for RET
    LD R6, EVALSAVER6       ;Load registers for RET
    LD R7, EVALSAVER7       ;Load registers for RET
    RET                     ;Return to where the subroutine was called




POP_SaveR3  .BLKW #1    ;Storage
POP_SaveR4  .BLKW #1    ;Storage
PUSH_SaveR3 .BLKW #1    ;Storage
PUSH_SaveR4 .BLKW #1    ;Storage
PLUS_SaveR7 .BLKW #1    ;Storage
MIN_SaveR4  .BLKW #1    ;Storage
MIN_SaveR7  .BLKW #1    ;Storage
MUL_SaveR5  .BLKW #1    ;Storage
MUL_SaveR4  .BLKW #1    ;Storage
MUL_SaveR3  .BLKW #1    ;Storage
MUL_SaveR7  .BLKW #1    ;Storage
DIV_SaveR7  .BLKW #1    ;Storage
DIV_SaveR5  .BLKW #1    ;Storage
DIV_SaveR4  .BLKW #1    ;Storage
DIV_SaveR3  .BLKW #1    ;Storage
EXP_SaveR3  .BLKW #1    ;Storage
EXP_SaveR4  .BLKW #1    ;Storage
EXP_SaveR5  .BLKW #1    ;Storage
EXP_SaveR6  .BLKW #1    ;Storage
EXP_SaveR7  .BLKW #1    ;Storage
PRINTHEXSAVER0  .BLKW #1    ;Storage
PRINTHEXSAVER1  .BLKW #1    ;Storage
PRINTHEXSAVER2  .BLKW #1    ;Storage
PRINTHEXSAVER3  .BLKW #1    ;Storage
PRINTHEXSAVER4  .BLKW #1    ;Storage
PRINTHEXSAVER5  .BLKW #1    ;Storage
PRINTHEXSAVER6  .BLKW #1    ;Storage
PRINTHEXSAVER7  .BLKW #1    ;Storage
EVALSAVER0  .BLKW #1    ;Storage
EVALSAVER00 .BLKW #1    ;Storage
EVALSAVER1  .BLKW #1    ;Storage
EVALSAVER2  .BLKW #1    ;Storage
EVALSAVER3  .BLKW #1    ;Storage
EVALSAVER4  .BLKW #1    ;Storage
EVALSAVER5  .BLKW #1    ;Storage
EVALSAVER6  .BLKW #1    ;Storage
EVALSAVER7  .BLKW #1    ;Storage
 
STACK_END   .FILL x3FF0 ;FILL
STACK_START .FILL x4000 ;FILL
STACK_TOP   .FILL x4000 ;FILL
R3TEST      .FILL x0004 ;FILL
R4TEST      .FILL x0003 ;FILL
NEWLINE     .FILL x0A   ;FILL
INVALID     .STRINGZ "Invalid Input"    ;FILL
NEGEQUAL    .FILL xFFC3 ;FILL
NEGSPACE    .FILL xFFE0 ;FILL
NEGZERO     .FILL xFFD0 ;FILL
NEGONE      .FILL xFFCF ;FILL
NEGTWO      .FILL xFFCE ;FILL
NEGTHREE    .FILL xFFCD ;FILL
NEGFOUR     .FILL xFFCC ;FILL
NEGFIVE     .FILL xFFCB ;FILL
NEGSIX      .FILL xFFCA ;FILL
NEGSEVEN    .FILL xFFC9 ;FILL
NEGEIGHT    .FILL xFFC8 ;FILL
NEGNINE     .FILL xFFC7 ;FILL
NEGPLUS     .FILL xFFD5 ;FILL
NEGMINUS    .FILL xFFD3 ;FILL
NEGMULT     .FILL xFFD6 ;FILL
NEGDIV      .FILL xFFD1 ;FILL
NEGEXP      .FILL xFFA2 ;FILL



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS    
;your code goes here
AND R0, R0, #0          ;Initialize R0 to 0
ADD R0, R3, R4          ;Add R3 and R4 together, putting the result into R0
RET                     ;Return to where the subroutine was called
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN
ST R4, MIN_SaveR4       ;Store R4 to be loaded back at the end
NOT R4, R4              ;Invert as the first step of finding two's compliment
ADD R4, R4, #1          ;Add R4 to find the two's compliment of R4
ADD R0, R3, R4          ;Subtract the two numbers together and store them in R0
LD R4, MIN_SaveR4       ;Restore R4 back
RET                     ;Return to where the subroutine was called
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL
ST R5, MUL_SaveR5       ;Store registuer for RET
ST R4, MUL_SaveR4       ;Store registuer for RET
ST R3, MUL_SaveR3       ;Store registuer for RET
AND R0, R0, #0          ;Initialize R0 to 0
ADD R3, R3, #0          ;Look at R3 for branch
BRn R3ISNEG             ;If R3 is negative, go to R3ISNEG
BRzp RESTORE            ;If it isn't don't change the values of R3 and R4
 
R3ISNEG                
    ADD R4, R4, #0      ;Look at R4
    BRn BOTHNEG         ;If R4 is negative, then change both R3 and R4 to positive
    BRzp RESTORE        ;If not, then restore R3 and R4 to their original values
BOTHNEG        
    NOT R3, R3          ;Invert R3
    ADD R3, R3, #1      ;Find two's complement of R3
    NOT R4, R4          ;Invert R4
    ADD R4, R4, #1      ;Find two's complement of R4
    BRnzp MULTLOOP      ;No matter what, go back to multiplication loop
 
RESTORE
    LD R3, MUL_SaveR3   ;Restore R3 to original value
    LD R4, MUL_SaveR4   ;Resotre R4 to original value
 
MULTLOOP    
    ADD R0, R0, R3      ;Add R3 to whatever is in R0 and store it in R0
    ADD R4, R4, #-1     ;Decrement the loop counter
    BRp MULTLOOP        ;Go to the top of the loop
 
LD R5, MUL_SaveR5       ;Load registers for RET
LD R4, MUL_SaveR4       ;Load registers for RET
LD R3, MUL_SaveR3       ;Load registers for RET
 
RET                     ;Return to where the subroutine was called
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0, R1
DIV
 
ST R3, DIV_SaveR3       ;Store registers for RET
ST R4, DIV_SaveR4       ;Store registers for RET
ST R5, DIV_SaveR5       ;Negative R4 in R5
AND R0, R0, #0          ;Initialize R0 to 0
LD R5, DIV_SaveR4       ;Load the value of R4 into R5
NOT R5, R5              ;Invert R5
ADD R5, R5, #1          ;Add one to R5 to find the two's complement for subtraction
DivLOOP
    ADD R0, R0, #1      ;Increase the division counter "R0"
    ADD R3, R3, R5      ;Subtract R4 (aka R5) from R3
    BRzp DivLOOP        ;Check to see if the result of the above expression is negative and if it is, then finish the loop
    ADD R0, R0, #-1     ;Subtract one from the division counter to take back the overdone subtraction and therefore make the remainder
 
LD R3, DIV_SaveR3       ;Load registers for RET
LD R4, DIV_SaveR4       ;Load registers for RET
LD R5, DIV_SaveR5       ;Load registers for RET
 
RET                     ;Return to where the subroutine was called
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
ST R3, EXP_SaveR3       ;Store registers for RET
ST R4, EXP_SaveR4       ;Store registers for RET
ST R5, EXP_SaveR5       ;Store registers for RET
ST R6, EXP_SaveR6       ;Store registers for RET
ST R7, EXP_SaveR7       ;Store registers for RET
LD R5, EXP_SaveR4       ;Store registers for RET
LD R4, EXP_SaveR3       ;Store registers for RET
ADD R5, R5, #-1         ;Subract one from the loop counter because if the exponent is 2, then you only need to multipy them together once etc.
 
ExpLOOP
    JSR MUL             ;Call the MUL subroutine as a nested subroutine to multiply the base by itself
    ADD R3, R0, #0      ;Store the solution of this nested subroutine in R3 so that it can be multiplied it by the original base again
    ADD R5, R5, #-1     ;Decrement the loop counter by one (Exponent - 1)
    BRp ExpLOOP         ;If the loop counter is either negative or zero, then exit the loop
 
ADD R0, R3, #0          ;Store the result into R0 as we are following the instrictions of the subroutine.
 
LD R3, EXP_SaveR3       ;Load registers for RET
LD R4, EXP_SaveR4       ;Load registers for RET
LD R5, EXP_SaveR5       ;Load registers for RET
LD R6, EXP_SaveR6       ;Load registers for RET
LD R7, EXP_SaveR7       ;Load registers for RET
 
RET                     ;Return to where the subroutine was called.
 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH    
    ST R3, PUSH_SaveR3  ;save R3
    ST R4, PUSH_SaveR4  ;save R4
    AND R5, R5, #0      ;
    LD R3, STACK_END    ;
    LD R4, STACK_TOP    ;
    ADD R3, R3, #-1     ;
    NOT R3, R3          ;
    ADD R3, R3, #1      ;
    ADD R3, R3, R4      ;
    BRz OVERFLOW        ;stack is full
    STR R0, R4, #0      ;no overflow, store value in the stack
    ADD R4, R4, #-1     ;move top of the stack
    ST R4, STACK_TOP    ;store top of stack pointer
    BRnzp DONE_PUSH     ;
OVERFLOW
    ADD R5, R5, #1      ;
DONE_PUSH
    LD R3, PUSH_SaveR3  ;
    LD R4, PUSH_SaveR4  ;
    RET
 
;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP
    ST R3, POP_SaveR3   ;save R3
    ST R4, POP_SaveR4   ;save R3
    AND R5, R5, #0      ;clear R5
    LD R3, STACK_START  ;
    LD R4, STACK_TOP    ;
    NOT R3, R3          ;
    ADD R3, R3, #1      ;
    ADD R3, R3, R4      ;
    BRz UNDERFLOW       ;
    ADD R4, R4, #1      ;
    LDR R0, R4, #0      ;
    ST R4, STACK_TOP    ;
    BRnzp DONE_POP      ;
UNDERFLOW
    ADD R5, R5, #1      ;
DONE_POP
    LD R3, POP_SaveR3   ;
    LD R4, POP_SaveR4   ;
    RET
 
.END
 