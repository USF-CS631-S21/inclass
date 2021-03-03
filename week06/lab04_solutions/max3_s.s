/* max3_s.s - find the maximum value of three arguments using max2 */

.global max3_s

max2_s:
    cmp r0, r1
    bgt max2_end
    mov r0, r1
max2_end:
    bx lr

/* v0 - r0
 * v1 - r1
 * v2 - r2
 */
max3_s:
    sub sp, sp, #8
    str lr, [sp]    

    str r2, [sp, #4]
    bl max2_s

    ldr r1, [sp, #4]
    bl max2_s

    ldr lr, [sp]
    add sp, sp, #8
    bx lr
