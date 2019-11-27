extern fgets
extern puts

SECTION .data

buffer: db `\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0` ;20 null bytes

; writestdout(buf, len):
%macro write 2
	mov rax, 1
	mov rdi, 1
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

SECTION .text

global assembler

assembler:
	enter 0, 0
    ;setup and call fgets
	mov rdi, buffer
	mov rsi, 20 ;max len
	mov rdx, 0 ;stdin
	call fgets

	mov rdi, buffer
	call puts
	
	leave
	ret


