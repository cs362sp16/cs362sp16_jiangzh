	; Name:	Zhi Jiang
	; Creation date: 01/02/2015
	; Last modified: 02/02/2015
	;
	; 
	; Name of file:	homework3_1
	; Description: The user enter a number between 1 to 46, and then print number of Fibonacci terms	 
	;		
	; Assemble:	nasm -f elf homework3_1.asm
	; Link:		gcc -m32 homework3_1.o -o homework3_1 
	; Run:		./template
	; Output:	1   1   2   3   5
	;		8   13		  	
	;
	; Declare needed external functions
	;  	
extern printf		; the C function, to be called
extern scanf		; C input function
			
SECTION .data			; data section, initialized variables
	num1: 		dd 1	; the number1 is used to calculate Fibonacci terms
	num2: 		dd 0	; the number2 is used to calculate Fibonacci terms
	a:		dd 37	; the number user enter 			
	min_val: 	dd 0	; minimum of the range
	max_val: 	dd 47	; maxinum of the range
	introduce:	db "Author: Zhi Jiang 	Program's name: Assignment 3", 10, 0
	get_name:	db "Can I have your name? ", 10, 0
	greet:		db 10, "Hello, %s! Welcome to use this program! Please enter number between 1 to 46", 10, 0
	yes: 		db "your value is in range", 10, 0
	no: 		db "your value is not in range", 10, 0
	play:		db 10,"You can enter a number if you would like to play again, or enter 0 for exit", 10, 0
	display:	db 10, "There are %d Fibonacci terms: ",10,0 
	exit:		db 10, "Have a good day, %s!", 10, 0  
	line:		db " ", 10, 0	
	print1: 	db "%d", 0
	print2: 	db "%d   ", 0 	
	print3:		db "%s", 0
SECTION .bss			; BSS, uninitialized variables	
	name:	resw	1	; the string user enter

SECTION .text			; Code section.

global main			; the standard gcc entry point

main:				; the program label for the entry point
	push 	ebp		; set up stack frame
	mov 	ebp,esp

.introduction:
	push	dword introduce	; print string 'introduce' to introduce author and program'name
	call	printf		
	add	esp, 4		

.get_name:
	push	dword get_name	; print string 'get_name' to ask users' name
	call	printf
	add	esp, 4

	push	dword name	; users enter their name
	push	dword print3
	call	scanf
	add	esp, 8

.greet_users:	
	push	dword name	; print string 'greet' to greet users and ask user enters a number
	push	dword greet	; in this string, user's name is included
	call	printf
	add	esp, 8

.get_user_data:		
	push 	dword a		; users enter a number
	push 	dword print1		
	call 	scanf
	add 	esp, 8

.check_number:	
	mov 	eax, [a]
	cmp 	eax, 0		; compare number users enter with zero 
	je 	.post_finish	; if number is equal to zero, and then jump to post_finish  

	cmp 	eax, [min_val]	; compare number users enter with 0 
	jle 	.failure	; if number is smaller than 0, and the jump to failure
	
	cmp 	eax, [max_val] 	; compare number users enter with 47 
	jge 	.failure	; if number is bigger than 0, and the jump to failure

.winner:
	push	dword [a]
	push	dword display	; make a title for the table 
	call	printf
	add	esp, 8
	
	mov	eax, 1		
	mov	[num1], eax	; initialize num1
	mov	eax, 0
	mov	[num2], eax	; initialize num2
	mov 	ecx, [a]	; initialize register ecx, loop will execute a times
	mov	edi, [a]	; initialize register edi		
	mov	esi, 5		; initialize register esi

.start_loop:
        cmp     esi, 0		; compare value in register esi with 0 
        je      .change_line	; if valueis equal to zero, and then jump to change_line
	sub	esi, 1		

.display_number:
	push	ecx		; begin using loop
	mov     ebx, [num1]	; move value in num1 to register ebx
        add     ebx, [num2]	; add value in num2 to register ebx
        push    dword ebx
        push    dword print2	
        call    printf		; print value in ebx, which is a Fibonacci term
        add     esp, 8
	
	mov     edx, [num2]	; move value in num2 to edx
        mov     [num1], edx	; move value in edx to num1
        mov     [num2], ebx	; nove value in ebx to num2
	
	pop	ecx		; loop completes one time
	
	sub	edi, 1		; the value in edi subtract one 
	cmp	edi, 0		; compare value in edi with 0
	je	.post_winner 	; if valueis equal to zero, and then jump to post_winner	
	
	loop	.start_loop	; loop again
	jmp	.post_winner	; jump to post_winner after loop finishs
	

.change_line:
	mov	esi, 4		

	push	dword line	; print a string 'line' to change line
	call	printf
	add	esp, 4
	jmp	.display_number


.failure:
	push 	no		; if the number is not in range, the massge will be printed 
	call 	printf
	add 	esp, 4
		
.post_failure:
	jmp 	.get_user_data	

.post_winner:
	push	dword line	
	call	printf
	push	dword play	; aks users if they want to play again
	call	printf
	
	jmp	.get_user_data	; jump to get_user_data

.post_finish:
	
	push	dword name	; print user's name	
	push	dword exit	; print parting message
	call	printf
	add	esp, 4

	mov 	esp, ebp	; takedown stack frame
	pop 	ebp		; same as "leave" op
	
	mov 	eax,0		; normal, no error, return value
	ret			; return 
