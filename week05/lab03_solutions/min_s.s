/* min_s.s - simple min function */

.global min_s

/* a is r0, b is r1 */
min_s:
    cmp r0, r1
    bge else
    b end
else:
    mov r0, r1
end:
    bx lr
