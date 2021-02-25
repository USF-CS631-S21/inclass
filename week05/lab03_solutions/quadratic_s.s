/* quadratic_s.s - quadratic function */

.global quadratic_s

/* x is r0, a is r1, b is r2, c is r3 */
quadratic_s:
    mul r1, r1, r0  /* (a * x) */
    mul r1, r1, r0  /* (a * x * x) */
    mul r2, r2, r0  /* (b * x) */
    add r0, r1, r2  /* (a * x * x) + (b * x) */
    add r0, r0, r3  /* (a * x * x) + (b * x) + c */
    bx lr
