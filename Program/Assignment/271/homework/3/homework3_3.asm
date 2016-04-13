     	; Name: Zhi Jiang
        ; Creation date: 01/02/2015
        ; Last modified: 02/02/2015
        ;
        ; 
        ; Name of file: homework3_3
        ; Description:  the program displays the integers from 9 through 5 in the form 98765 using a counted loop        
        ;               
        ; Assemble:     nasm -f elf homework3_3.asm
        ; Link:         gcc -m32 homework3_3.o -o homework3_3 
        ; Run:          ./homework3_3
        ; Output:       98765             
        ;
        ; Declare needed external functions
        ;       
extern printf		; the C function, to be called
	
SECTION .data			; data section, initialized variables
	num:		dd 9	; first number is 9		
	time:		dd 5	; loop 5 times
	print:		db "%d", 0
	line:		db " ", 10, 0

SECTION .bss			; BSS, uninitialized variables 

SECTION .text			; Code section.

global main			; the standard gcc entry point

main:				; the program label for the entry point
	push	ebp		; set up stack frame
	mov	ebp, esp
	
.start:
	mov	ecx, [time]	; initialize register ecx, loop will execute 5 times

.loop:
	push	ecx
	
	mov	eax, [num]	; move value in num to register eax
	push	dword eax	
	push	dword print	; print this value
	call	printf
	add	esp, 8

.calculate:
	mov	ebx, [num]	; move value in num to ebx
	sub	ebx, 1		; calculate next number we nedd
	mov	[num], ebx 	; move the new value in num
	
	pop	ecx	

	loop	.loop		; complete one loop

.finish:
	push	dword line
	call	printf
	add	esp, 4

	mov	esp, ebp	; takedown stack frame
	pop	ebp		; same as "leave" op
	
	mov	eax, 0		; normal, no error, return value
	ret			; return 

