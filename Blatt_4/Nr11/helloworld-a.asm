SECTION .data

; lege hello world string in Speicher
str:	db `Hello world!\n`
; lege länge des hello world strings in Speicher
strlen: equ $ - str

; TODO: remove
num:	dq 1337

SECTION .text

; mache Einstiegspunkt von außen sichtbar
global _start

; Einstiegspunkt in das Programm
_start:
	mov	rax, 1 ; syscall code für write
	mov	rdi, 1 ; fd für std out
	mov	rsi, str ; string, welcher außgegeben werden soll
	mov	rdx, strlen ; länge des strings
	syscall ; führe syscall auß

	mov	rax, 60 ; syscall code für sys_exit
	mov	rdi, 0 ; error code 0
	syscall ; führe syscall auß