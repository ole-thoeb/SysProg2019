SECTION .data

writebuf:	db 0

; writestdout(buf, len):
%macro write 2
	mov rax, 1
	mov rdi, 1
	mov rsi, %1
	mov rdx, %2
	syscall
%endmacro

%macro pnumbersave 1
	push rax
	push rdi
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	push r10
	push r11

	push 10
	push %1
	call printnumber
	
	add rsp, 0x10

	pop r11
	pop r10
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	pop rax
%endmacro

global m_add

SECTION .text


;rdi = n, 
;rsi = m, 
;rdx = M1, 
;rcx = M2, 
;r8 = R

m_add:
	push rbp
	mov rbp, rsp

	mov r9, 0 ;y = 0
.outerloop
	cmp r9, rdi
	jge .endouter ;end loop if y >= n
	mov r10, 0 ; x = 0
.innerloop
	cmp r10, rsi ; x = 0
	jge .endinner ;end loop if x >= m
	
	push rdx ;save M1

	; calculate offset
	mov rax, r9
	mul rsi ;rdx:rax = y * m
	add rax, r10 ; y * m + x

	;pnumbersave rax
	;mult offset by 4 (sizeof(int))
	mov rdx, 4
	mul rdx 

	pop rdx ; restor M1

	mov r11, [rdx + rax]

	;pnumbersave r11

	add r11, [rcx + rax]
	mov [r8 + rax], r11
	inc r10 ;x++
	jmp .innerloop
.endinner
	inc r9; y++
	jmp .outerloop
.endouter
	leave
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
