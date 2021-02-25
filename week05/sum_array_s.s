.global sum_array_s

/*
Sum len elments in array.
Use pointer update to access array elements.


Map of registers to C variables.

r0 - array
r1 - len

r2 - i
r3 - sum

*/

sum_array_s:
    mov r2, #0      /* i = 0 */
    mov r3, #0      /* sum = 0 */
loop:               /* top of loop */
    cmp r2, r1      /* cmp i to len */
    beq loop_exit   /* if i == len, then exit loop */
    ldr r12, [r0]   /* r12 = *array */
    add r3, r3, r12 /* sum = sum + r12 */
    add r2, r2, #1  /* i = i + 1 */
    add r0, r0, #4  /* array = array + 4 (next int) */
    b loop          /* branch to loop: */
loop_exit:
    mov r0, r3      /* r0 = sum (return value) */
    bx lr           /* return to caller */
