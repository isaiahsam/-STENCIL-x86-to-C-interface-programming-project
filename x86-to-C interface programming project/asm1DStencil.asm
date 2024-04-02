section .data
output_format db "(ASM) Computed Y: %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, %.4lf, ...", 10, 0

section .text
bits 64
default rel

global asm1DStencil
extern printf

; Performs 1D stencil operation on a double precision floating point array
; @param rcx - size of the arrays (n)
; @param rdx - pointer to the input array (X)
; @param r8 - pointer to the output array (Y)
asm1DStencil:
    sub rsp, 128          ; Reserve stack space for local variables and alignment
    
    mov rsi, rdx          ; RSI points to the start of X
    mov rdi, r8           ; RDI points to the start of Y
    xor rdx, rdx          ; RDX will keep count of processed elements for Y
    
    ; Zeroing out registers used for sums to ensure clean state
    xorpd xmm0, xmm0
    xor r9, r9            ; Counter for the main loop

MainLoop:
    cmp r9, rcx
    jge Finish            ; Jump to finish when all elements processed
    
    ; Reset xmm0 for new sum
    xorpd xmm0, xmm0
    
    ; Load and sum 7 consecutive elements from X into xmm0
    movsd xmm1, [rsi + r9*8 - 24] ; X[i-3]
    addsd xmm0, xmm1
    movsd xmm1, [rsi + r9*8 - 16] ; X[i-2]
    addsd xmm0, xmm1
    movsd xmm1, [rsi + r9*8 - 8]  ; X[i-1]
    addsd xmm0, xmm1
    movsd xmm1, [rsi + r9*8]      ; X[i]
    addsd xmm0, xmm1
    movsd xmm1, [rsi + r9*8 + 8]  ; X[i+1]
    addsd xmm0, xmm1
    movsd xmm1, [rsi + r9*8 + 16] ; X[i+2]
    addsd xmm0, xmm1
    movsd xmm1, [rsi + r9*8 + 24] ; X[i+3]
    addsd xmm0, xmm1
    
    ; Store the sum in Y
    movsd [rdi + r9*8], xmm0
    
    inc r9
    jmp MainLoop

Finish:
    ; Determine the number of results to print (minimum of r9 and 10)
    cmp r9, 10
    jle PreparePrint
    mov r9, 10

PreparePrint:
    lea rcx, [output_format] ; Message format
    ; Assuming we want to print the first 10 or fewer elements
    ; Load up to 10 elements from Y into registers for printf
    ; We start from the last element to print and move backwards
    mov rax, rdi
    add rax, 8*9          ; Adjust rax to point to the 10th element or last
    movq xmm1, [rax-72]  ; Y[0] or earlier
    movq xmm2, [rax-64]
    movq xmm3, [rax-56]
    movq xmm4, [rax-48]
    movq xmm5, [rax-40]
    movq xmm6, [rax-32]
    movq xmm7, [rax-24]
    movq xmm8, [rax-16]
    movq xmm9, [rax-8]
    movq xmm0, [rax]     ; Y[9] or last available
    sub rsp, 8*4         ; Shadow space for Windows ABI
    call printf          ; Print the elements
    add rsp, 8*4         ; Clean up shadow space

    add rsp, 128         ; Restore stack space
    ret                  ; Return to caller
