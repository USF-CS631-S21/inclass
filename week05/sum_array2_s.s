.global sum_array2_s

/*
Sum len elements in array.
Use indexing to access array elements.

Map of registers to C variables.

r0 - array
r1 - len

r2 - i
r3 - sum

*/

sum_array2_s:
    mov r2, #0      /* i = 0 */
    mov r3, #0      /* sum = 0 */
loop:               /* top of loop */
    cmp r2, r1      /* cmp i to len */
    beq loop_exit   /* if i == len, then exit loop */
    ldr r12, [r0, r2, LSL #2]  /* r12 = array[i] */
    add r3, r3, r12 /* sum = sum + r12 */
    add r2, r2, #1  /* i = i + 1 */
    b loop          /* branch to loop: */
loop_exit:
    mov r0, r3      /* r0 = sum (return value) */
    bx lr           /* return to caller */
