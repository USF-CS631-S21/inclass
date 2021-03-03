/* fib_rec_s - recursive fibanocci */

.global fib_rec_s

fib_rec_s:
    sub sp, sp, #16
    str lr, [sp]

    cmp r0, #0
    beq exit
    cmp r0, #1
    beq exit

    str r0, [sp, #4]
    sub r0, r0, #1
    bl fib_rec_s

    str r0, [sp, #8]  // put fib_rec_s(n-1) on stack
    ldr r0, [sp, #4]
    sub r0, r0, #2
    bl fib_rec_s
    ldr r1, [sp, #8] 
    add r0, r1, r0

exit:
    ldr lr, [sp]
    add sp, sp, #16
    bx lr
