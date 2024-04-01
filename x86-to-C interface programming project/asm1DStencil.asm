section .data
msg db "Hello World", 13,10,0

section .text
bits 64
default rel

global asmStencil
extern printf

asmStencil: 
	sub rsp, 8*5
	lea rxc, [msg]
	call printf
	add rsp, 8*5
	ret


; trial

section .data
    n dq 8                 ; Length of the vector
    X dq 1, 2, 3, 4, 5, 6, 7, 8 ; Source vector
    Y dq 0, 0, 0, 0, 0, 0, 0, 0 ; Destination vector

section .text
global _start

_start:
    mov rsi, 3            ; Start index at 3 because we need X[i-3]
    mov rcx, n            ; Counter for loop, set to n
    sub rcx, 3            ; Adjust loop for starting index

loop_start:
    mov rax, [X + rsi*8 - 24] ; X[i-3]
    add rax, [X + rsi*8 - 16] ; X[i-2]
    add rax, [X + rsi*8 - 8]  ; X[i-1]
    add rax, [X + rsi*8]      ; X[i]
    mov [Y + rsi*8], rax      ; Store result in Y[i]

    inc rsi              ; Move to the next element
    loop loop_start      ; Loop until rcx is 0

    ; Code to display the first ten elements of Y would go here
    ; This is platform-specific and requires system calls or external library functions

    ; Exit the program (This is just a placeholder, actual exit code will depend on the environment)
    mov rax, 60          ; syscall number for exit
    xor rdi, rdi         ; status 0
    syscall
