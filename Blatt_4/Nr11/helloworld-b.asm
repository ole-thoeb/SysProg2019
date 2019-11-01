SECTION .data

; lege hello world string in Speicher
str:	db `Hello world!\n`
; lege länge des hello world strings in Speicher
strlen: equ $ - str

num:	dq 1234

numbuffer: db `abcdefghijklmnopqrs\n` ; 8 byte buffer

constzero: dq 0

star: db '*'

%macro write 2
	mov	rax, 1 ; syscall code für write
	mov	rdi, 1 ; fd für std out
	mov	rsi, %1 ; string, welcher außgegeben werden soll
	mov	rdx, %2 ; länge des strings
	syscall ; führe syscall aus
%endmacro

SECTION .text

; mache Einstiegspunkt von außen sichtbar
global _start

; Einstiegspunkt in das Programm
_start:

	write numbuffer, 20
	mov r12, 10
	mov r13, 0
	mov r14, num
	numloop:
		mov rdx, 0 ; set rdx to 0 because its get used in division (rax = rdx:rax /op)
		mov rax, r14 
		div r12 ; r14 / 10
		mov r14, rax ;set r14 to the result of the divison
		mov r15, rdx
		add r15, 48; add ascii base to remainder
		mov byte [numbuffer + r13], byte r15b ; write last byte of rax to buffer
		inc r13 ; increment buffer pos to write to
		
		mov byte [numbuffer + r13], 10
		inc r13
		write numbuffer, r13
		dec r13

		cmp r14, 0
		jnz numloop

	write numbuffer, r13

	mov	rax, 60 ; syscall code für sys_exit
	mov	rdi, 0 ; error code 0
	syscall ; führe syscall aus