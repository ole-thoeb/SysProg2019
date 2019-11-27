SECTION .data

; define the fibonacci number that should be calculated
n:      dq   10

writebuf:	db 0

msg: db `hi\n`
msglen: equ $ - msg

; writestdout(buf, len):
%macro write 2
	mov rax, 1
	mov rdi, 1
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

SECTION .text

global _start

_start:
    ; call Fibonacci function f(n)
    ;mov     rdi, [n]    ; parameter: fibonacci number to calculate
	push qword[n]
    call f           ; call function

    ; print calculated Fibonacci number on stdout
	push 10
	push rax
    call    printnumber

    ; exit process with exit code 0
    mov     rax, 60
    mov     rdi, 0
    syscall
 
; f: Calculates a Fibonacci number
;   f(n) = {n, if n<=1; f(n-1)+f(n-2), else}.
;   Parameter: Integer n >= 0, passed on stack
;   Returns:   Fibonacci number f(n), returned in rax
f:
	;set up stack frame
	push rbp  ;save base pointer
	mov rbp, rsp ; set base pointer to stack pointer

	mov r8, qword[rbp + 0x10] ; get n

	;push 10
	;push r8
	;call printnumber
	;pop r8
	;pop r8
	;mov r8, qword[rbp + 0x10] ; get n

	cmp r8, 1 ; compare n to 1
	jle .breakcon ; jump if (n <= 1)

	dec r8 ; n-1
	push r8 ;set parameter for f
	call f
	pop r8
	push rax ;save result
	dec r8 ; n-2
	push r8 ;set parameter for f
	call f
	pop r8 ;discard call parameter
	pop r8 ;retrive result
	add rax, r8 ;result = f(n-2) + f(n-1)
	jmp .fend

.breakcon 
	mov rax, r8 ; set n as return value
.fend leave
    ret



printnumber:
	; stack setup
	push rbp
	mov rbp, rsp

	mov r8, qword[rsp + 0x10]	; num
	mov r9, qword[rsp + 0x18]	; base
	mov r10, 0			; numlen
	
	; if zero, print 0
	test r8, r8
	jz .pzero

	; conversion base 10
	; break when the number is gone
.loop	mov rax, r8
	test rax, rax
	jz .print

	; divide
	mov rdx, 0	; mod reset
	div r9

	; add ascii '0', push to stack
	mov r8, rax
	add rdx, '0'
	push rdx
	
	; inc length
	add r10, 1

	jmp .loop

	; break when the length is gone
.print	test r10, r10
	jz .end

	; get the latest digit from the stack
	pop rax
	mov byte [writebuf], al

	; print the digit
	write writebuf, 1

	; decrease the length
	sub r10, 1
	jmp .print

; print zero
.pzero 	mov byte [writebuf], '0'
	write writebuf, 1
	jmp .end

; cleanup
.end	mov byte [writebuf], 0x0A	;newline
	write writebuf, 1

	; restore stack pointers
	mov rsp, rbp
	pop rbp

	ret


; nasm -felf64 fibonacci-stub.asm && ld fibonacci-stub.o && ./a.out