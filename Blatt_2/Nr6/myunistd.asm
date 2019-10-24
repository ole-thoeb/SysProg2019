
;ruft den syscall mit Nr. %1 auf.
;%2-$5 sind die ersten vier argumente, welche mit übergeben werden
%macro syscall4arg 5
	mov rax, %1
	mov rdi, %2
	mov rsi, %3
	mov rdx, %4
	mov r10, %5
	syscall

	ret
%endmacro

global myread
global mywrite
global myclose
global mydup2
global myfork
global myexecve
global mywait4
global mychdir
global mychdir
global myexit

;ruft den syscall mit Nr. %1 auf.
;%2-$5 sind die ersten vier argumente, welche mit übergeben werden
%macro syscall3arg 4
	syscall4arg %1, %2, %3, %4, 0
%endmacro

SECTION .text

myread:
	syscall3arg 0, rdi, rsi, rdx

mywrite:
	syscall3arg 1, rdi, rsi, rdx

myclose:
	syscall3arg 3, rdi, 0, 0

mypipe:
	syscall3arg 22, rdi, 0, 0

mydup2:
	syscall3arg 33, rdi, rsi, 0

myfork:
	syscall3arg 57, 0, 0, 0

myexecve:
	syscall3arg 59, rdi, rsi, rdx

mywait4:
	syscall4arg 61, rdi, rsi, rdx, rcx

mychdir:
	syscall4arg 80, rdi, 0, 0, 0

myexit:
	syscall4arg 231, rdi, 0, 0, 0