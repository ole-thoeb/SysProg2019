# syscall hull
%macro syscallHull 1
	mov rax, %1
	syscall
	ret
%endmacro

global myread
global mywrite
global myclose
global mypipe
global mydup2
global myfork
global myexecve
global mywait4
global mychdir
global myexit

SECTION .text

myread:
	syscallHull 0

mywrite:
	syscallHull 1

myclose:
	syscallHull 3

mypipe:
	syscallHull 22

mydup2:
	syscallHull 33

myfork:
	syscallHull 57

myexecve:
	syscallHull 59

mywait4:
	syscallHull 61

mychdir:
	syscallHull 80

myexit:
	syscallHull 231
