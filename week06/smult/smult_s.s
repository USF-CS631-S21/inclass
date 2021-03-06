.global smult_s


/*

r0 - int *array
r1 - int len
r2 - int s

r3 - int i
*/

smult_s:
    mov r3, #0

loop:
    cmp r3, r1
    beq exit
    ldr r12, [r0, r3, LSL #2]
    mul r12, r2, r12
    str r12, [r0, r3, LSL #2]
    add r3, r3, #1
    b loop

exit:    
    bx lr 
