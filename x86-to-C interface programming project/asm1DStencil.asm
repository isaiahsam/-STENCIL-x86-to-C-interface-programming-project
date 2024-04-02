section .text
bits 64
default rel

global asm1DStencil

asm1DStencil:
    sub rsp, 8*11

    ; rsi - length, rdx - inputArray, r8 - outputArray
    mov rsi, rcx    ; Length of the array
    mov rdx, rdx    ; Address of inputArray
    mov rdi, r8     ; Address of outputArray

    ; Index initialization
    xor rax, rax    ; Zero out rax to use as our index

LOOP:
    cmp rax, rsi
    jge end         ; Jump to end if rax >= length (rsi)

    ; Skip the first 3 and last 3 elements by starting from index 3 and ending at length - 3
    cmp rax, 3
    jl SKIP_INCREMENT
    cmp rax, rsi
    jge SKIP_INCREMENT

    ; Stencil computation
    xorpd xmm0, xmm0           ; Clear xmm0
    movsd xmm1, [rdx+rax*8-24] ; Load inputArray[index-3]
    addsd xmm0, xmm1
    movsd xmm1, [rdx+rax*8-16] ; Load inputArray[index-2]
    addsd xmm0, xmm1
    movsd xmm1, [rdx+rax*8-8]  ; Load inputArray[index-1]
    addsd xmm0, xmm1
    movsd xmm1, [rdx+rax*8]    ; Load inputArray[index]
    addsd xmm0, xmm1
    movsd xmm1, [rdx+rax*8+8]  ; Load inputArray[index+1]
    addsd xmm0, xmm1
    movsd xmm1, [rdx+rax*8+16] ; Load inputArray[index+2]
    addsd xmm0, xmm1
    movsd xmm1, [rdx+rax*8+24] ; Load inputArray[index+3]
    addsd xmm0, xmm1

    ; Store the result into the output array
    movsd [rdi+rax*8], xmm0

SKIP_INCREMENT:
    inc rax        ; Increment our index
    jmp SHORT LOOP ; Jump back to the start of the loop

end:
    add rsp, 8*11
    ret
