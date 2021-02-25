#include <stdio.h>

int main(int argc, char **argv) {
    int x = 10;
    int y = 2;
    int z = 3;
    int r1;
    int r2;

    r1 = x / y;
    r2 = x / z;

    printf("r1 = %d\n", r1);
    printf("r2 = %d\n", r2);    

    return 0;

}
