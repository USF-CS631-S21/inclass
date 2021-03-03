int foo(int a) {
    int r = 0;
    
    if ((a == 3) || (a == 7)) {
        r = 1;    
    }

    return r;
}

/*

foo:

    cmp r0, #3
    beq true
    cmp r0, #7
    bne exit
true:
    mov r0, #1

exit:
    bx lr

*/
