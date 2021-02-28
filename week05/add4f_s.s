.global add4f_s

add2f_s:
    add r0, r0, r1
    bx lr

add4f_s:
    sub sp, sp, #8
    str lr, [sp]

    bl add2f_s
    str r0, [sp, #4]

    mov r0, r2
    mov r1, r3
    bl add2f_s

    ldr r1, [sp, #4]
    add r0, r0, r1

    ldr lr, [sp]
    add sp, sp, #8
    bx lr
    
