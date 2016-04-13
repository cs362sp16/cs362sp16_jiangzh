     	; Name: Zhi Jiang
        ; Creation date: 01/02/2015
        ; Last modified: 02/02/2015
        ;
        ; 
        ; Name of file: homework3_2
        ; Description: The program is used to calculate sum of numer users nter and average of these number        
        ;               
        ; Assemble:     nasm -f elf homework3_2.asm
        ; Link:         gcc -m32 homework3_2.o -o homework3_2 
        ; Run:          ./homework3_2
        ; Output:       
        ;                         
        ;
        ; Declare needed external functions
        ;    
extern	printf		; the C function, to be called
extern	scanf		; C input function
	
SECTION .data			; data section, initialized variables
	time:		dd 0	; initialize time
	sum:		dd 0	; initialize sum
	a:		dd 17	; the number user enter
	;num:		dd 1	; minimum of the r
	min_val:	dd 0	; minmum of the range
	max_val:	dd 101	; maximum of the range
	introduce:      db "Author: Zhi Jiang   Program's name: Assignment 3", 10, 0
	get_name:       db "Can I have your name? ", 10, 0
	greet:          db 10, "Hello, %s! Welcome to use this program! Please enter number between 0 to 100", 10, 0
	ask:	        db 10, "You can enter a number if you would like to enter again, or enter negative number for exit", 10, 0
	result:		db 10, "Your sum of all number is %d " , 0
	result1:        db "and your average of all number is %d" , 10, 0
	no:		db "The number you enter is not in range!" , 10, 0	 
	exit:           db "Have a good day, %s", 10, 0 
	print1:		db "%d", 0
	print2:		db "%s", 0

SECTION .bss			; BSS, uninitialized variables 
	name:		resw 1  ; the string user enter for name

SECTION .text			; Code section.
	
global main			; the standard gcc entry point
		
main:				; the program label for the entry point	
	push    ebp             ; set up stack frame
        mov     ebp,esp
	
	mov	ebx, 0		; empty register ebx		
	mov	esi, 0		; empty regsiter esi	

.introduction:
        push    dword introduce ; print string 'introduce' to introduce author and program'name
        call    printf
        add     esp, 4

.get_name:
        push    dword get_name	; print string 'get_name' to ask users' name
        call    printf
        add     esp, 4

        push    dword name	 ; users enter their name
        push    dword print2
        call    scanf
        add     esp, 8

.greet_users:
        push    dword name	; print string 'greet' to greet users and ask user enters a number
        push    dword greet	; in this string, user's name is included
        call    printf
        add     esp, 8

.get_user_data:
        push    dword a		; users enter a number
        push    dword print1
        call    scanf
        add     esp, 8

.check_number:
        mov     eax, [a]

        cmp     eax, [min_val]	; compare number users enter with -1 
        jle     .failure_2	; if number is equal to zero, and then jump to failure_2  

        cmp     eax, [max_val]	; compare number users enter with 101  
        jge     .failure_1	; if number is equal to zero, and then jump to failure_1 

.sum_num:
	mov	eax, 1
	add	[time], eax	; time is used to how many times the user enter
	
	mov	eax, [a]	
	add	[sum], eax	; sum is used to collect number the user enter

	push	dword ask	
	call	printf
	add	esp, 4

	jmp	.get_user_data	; jump to get_user_data 

.failure_1:
	push	no		; if the number is not in range, the massge will be printed 
	call	printf
	add	esp, 8

	jmp	.get_user_data	; jump to get_user_data

.failure_2:
	push	dword [sum]	
	push	dword result	; print sum of all number
	call	printf
	add	esp, 8

	mov	eax, [sum]	; calculate average of all number
	mov	ebx, [time]
	mov	edx, 0
	div	ebx

	push    dword eax
        push    dword result1	; print average 
        call    printf
        add     esp, 8
	
	push    dword name	; print user's name 
        push    dword exit	; print parting message
        call    printf
        add     esp, 8

        mov     esp, ebp        ; takedown stack frame
        pop     ebp             ; same as "leave" op

        mov     eax,0           ; normal, no error, return value
        ret			; return 

