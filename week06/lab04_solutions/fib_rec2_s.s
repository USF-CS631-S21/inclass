/* fib_rec_s - recursive fibanocci */

.global fib_rec2_s

fib_rec2_s:
    sub sp, sp, #16
    str lr, [sp]
    str r4, [sp, #4]
    str r5, [sp, #8]

    cmp r0, #0
    beq exit
    cmp r0, #1
    beq exit

    mov r4, r0
    sub r0, r0, #1
    bl fib_rec_s

    mov r5, r0
    mov r0, r4
    sub r0, r0, #2
    bl fib_rec_s
    mov r1, r5
    add r0, r1, r0

exit:
    ldr r5, [sp, #8]
    ldr r4, [sp, #4]
    ldr lr, [sp]
    add sp, sp, #16
    bx lr
