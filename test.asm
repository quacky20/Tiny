global _start
_start:
    mov rax, 60
    ; *! this moves 60 into the rax register
    mov rdi, 69
    syscall
    ; * so rax is the code of the command and rdi is the arg0. more can be found by checking linux syscalls

    