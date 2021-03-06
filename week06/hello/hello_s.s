/* hello_s.s - hello world in ARM assembly language */

/* External labels (functions) */
.global printf
.global find_max_s

/* .data designed data definitons, like C globals */
.data

/* The greeting label designates an address to the following string. */
/* The .asciz directive means the string is null terminated. */
greeting:
 .asciz "find_max([2,3,1], 3) = %d\n"   

/* Tell the assembler the following section contains code. */
.text
 
.global main
main:
    /* Make space on the stack */
    sub sp, sp, #16
    /* Put the value in lr (link register) onto the stack */
    str lr, [sp, #12]
    mov r0, #2
    str r0, [sp]
    mov r0, #3
    str r0, [sp, #4]
    mov r0, #1
    str r0, [sp, #8]

    mov r0, sp
    mov r1, #3

    bl find_max_s

    mov r1, r0

    /* Put the address of greeting into register r0 */
    ldr r0, =greeting
    
    /* Call printf() from C Library */
    bl printf

    /* Restore lr from stack so that the bx lr below returns to the */
    /* right location. */
    
    ldr lr, [sp, #12]
    /* Deallocate space on the stack */
    add sp, sp, #8
    bx lr

