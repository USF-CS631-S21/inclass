#include <stdio.h>
#include <stdlib.h>

/* A global variable definition */
int x;

int main(int argc, char **argv) {
    /* Local variable definitions - allocated on the stack */
    int y;
    int *z_p;

    /* Heap-based memory allocation */
    z_p = (int *) malloc(sizeof(int));
    
    x = 1;
    y = 2;
    *z_p = 3;
    
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z_p = %d\n", *z_p);

    return 0;
}
