/* stolower_s - covert upper case chars to lower case chars in s */

.global stolower_s

/*

r0 - char *s

*/

stolower_s:

loop:
    ldrb r1, [r0]
    cmp r1, #0
    beq exit
    cmp r1, #'A'
    blt next
    cmp r1, #'Z'
    bgt next
    add r1, r1, #32
    strb r1, [r0]
next:
    add r0, r0, #1  
    b loop
exit:
    bx lr
