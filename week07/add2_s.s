.global add2_s

add2_s:
    add r2, r0, r1
    add r0, r2, #99
    bx lr
