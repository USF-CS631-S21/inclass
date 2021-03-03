/* find_max_s - find the maximum value in an interger array */

.global find_max_s

/*

r0 - int *array
r1 - n

r2 - i
r3 - max

*/
    
find_max_s:
    mov r2, #1
    ldr r3, [r0]

loop:
    cmp r2, r1
    bge exit
    ldr r12, [r0, r2, LSL #2]
    cmp r12, r3
    ble next
    mov r3, r12
next:
    add r2, r2, #1
    b loop

exit:
    mov r0, r3
    bx lr
