/* max3_s.s - find the maximum value of three arguments using max2 */

main:
    mov r0, #1          @ set up parameters
    mov r1, #2
    mov r2, #3
    bl max3_s
    add r0, r0, #0      @ end marker
    
max2_s:
    cmp r0, r1
    bgt max2_end
    mov r0, r1
max2_end:
    bx lr

/* r0 - v0
 * r1 - v1
 * r2 - v2
 */
max3_s:
    sub sp, sp, #8
    str lr, [sp]

    bl max2_s

    mov r1, r2
    bl max2_s

    ldr lr, [sp]
    add sp, sp, #8
    bx lr
