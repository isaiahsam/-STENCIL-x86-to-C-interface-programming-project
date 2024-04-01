section .data
msg db "Hello World", 13,10,0

section .text
bits 64
default rel

global asmStencil
extern printf

asmStencil: 
	mov rax, 10
	ret