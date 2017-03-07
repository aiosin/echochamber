#include "echochamber.h"
/* enable intel asm syntax*/
.intel_syntax noprefix

/* .text marks the executable code section of the asm file */
.text
    /* exposes _start and syscall5 fucntion to the world */
    .globl _start, syscall5
    .globl syscall1, syscall2, syscall3, syscall4, syscall5


    _start:
        xor rbp, rbp /*setting rbp to 0*/
        pop rdi /* pop argc from the stack and increase the stack pointer by 8*/
        mov rsi, rsp
        and rsp, -16
        call main
        mov rdi, rax /*system call param 1 = ret value of main (rax)*/
        mov rax, SYS_exit
        syscall /*^mov 60 into rax/eax and call int x80, which is system exit*/
        ret

    syscall:
        mov rax,rdi
        syscall
        ret

    syscall1:
        mov rax,rdi
        mov rdi,rsi
        syscall
        ret

    syscall2:
        mov rax,rdi
        mov rdi,rsi
        mov rsi,rdx
        syscall
        ret

    syscall3:
        mov rax,rdi
        mov rdi,rsi
        mov rsi,rdx
        mov rdx,rcx
        syscall
        ret

    syscall4:
        mov rax,rdi
        mov rdi,rsi
        mov rsi,rdx
        mov rdx,rcx
        mov r10,r8
        syscall
        ret

    syscall5:
        mov rax,rdi
        mov rdi,rsi
        mov rsi,rdx
        mov rdx,rcx
        mov r10,r8
        mov r8,r9
        syscall
        ret
