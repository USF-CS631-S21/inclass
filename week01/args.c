#include <stdio.h>

/* The argc paramter is the number number of command line arguments. */
/* This includes the command path at argv[0]. */
/* The argv paramter is an array of pointers to strings. */
int main(int argc, char **argv) {
    int i;

    for (i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    
    return 0;
}
