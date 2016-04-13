	; Name: Zhi Jiang
	; Creation date: 22/01/2015
	; Last modified: 23/01/2015
	;
	;
	; Name of file: homework1.asm
	; Description:	this program has two parts. One is to display author's name and program's name. Second is to use four basic operation for two number users enter 
	; Assmeble: 	nasm -f elf homework1.asm
	; Link: 	gcc -m32 homework1.o -o homework1
	; Run:		./homework1
	; Output:	
	;
	; Equivalent C++ code
	; #inclide<iostream>{
	; 	int a, b;
	;	cout << "Name of Program: homework1 ";
	;	cout << "Author: Zhi Jiang " << endl;
	; 	cout << "Please enter two number: " << endl;
	;	cin >> a >> b;	
	;	cout << "sum: " << a+b << endl << "difference: " << a-b << endl << "produce: " << a*b << endl << "quotient: " << a/b << endl << "remainder: " << a%b << endl;
	;	cout << "The program has done, goodbye";
	;	return 0;
	; }
	;
	; Declare needed external functions
	;
	extern printf                           ; the C function, to be called
        extern scanf				; the C input function 

SECTION .data					; Data section, inialized variables
	author: 	db "Author: Zhi Jiang ", 10, 0   
	name:		db "Name of program: homework1 ", 0
	ask:		db "Please enter two numbers: ", 10, 0
	getnumber:	db "%d %d", 0
	addition:	db "the sum of these two number is %d", 10, 0
	substrction:	db "the difference of these two number is %d", 10, 0
	multiplication:	db "the produce of these two number is %d", 10, 0
	division:	db "the quotient of these two number is %d, and the remider of these two number is %d", 10, 0
	finish:		db "The program has done, goodbye", 10, 0

SECTION .bss					; BSS, unitialized variables
	int1: 		resd 1
	int2: 		resd 1

SECTION .text					; code section.
	
	global main				; the standard gcc entry point
	
	main:					; the program label for the entry point
		push ebp			; set up stack frame
		mov  ebp,esp

		push dword name			; this part is about author and name of programe
		call printf
		push dword author	
		call printf
		add  esp, 8

		push dword ask			; this part is about entering number
		call printf
		add  esp, 8

		push dword int2			; this part is about users enter number
		push dword int1
		push dword getnumber
		call scanf
		add  esp, 8

 		
		mov  eax, [int1]		; this part is about addition
		add  eax, [int2]
		push dword eax
		push dword addition
		call printf
		add  esp, 8
		

		mov  ebx, [int1]		; this part is about substrction
		sub  ebx, [int2]
		push dword ebx
		push dword substrction
		call printf
		add  esp, 8
		
		
		mov  eax, [int1]		; this part is about multiplication
		mov  ebx, [int2]
		mul  ebx
		push dword eax
		push dword multiplication
		call printf 
		add  esp, 8	

		mov  eax, [int1]		; this part is about division:
		mov  ebx, [int2]
		mov  edx, 0
		div  ebx
		push dword edx
		push dword eax
		push dword division
		call printf
		add  esp, 8
		
		push dword finish		; thus part is about termination message
		call printf
		add  esp, 8

		mov  esp,ebp			; takedown stack frame
		pop  ebp			; same as "leave" up
		mov  eax, 0			; normal, no error, return valuse
 		ret				; return 
