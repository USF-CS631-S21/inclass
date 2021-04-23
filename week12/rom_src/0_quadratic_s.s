main:
    mov r0, #1          @ set up parameters
    mov r1, #1
    mov r2, #1
    mov r3, #1
    bl quadratic_s
    add r0, r0, #0      @ end marker
    
quadratic_s:
    mul r12, r0, r0
    mul r1, r12, r1
    mul r2, r0, r2
    add r0, r1, r2
    add r0, r0, r3
    bx lr
