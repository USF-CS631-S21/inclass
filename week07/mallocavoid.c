#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char * uint32_to_binstr_wrong(uint32_t value) {
    char s[64];
    char *p = s;
    int i;
    int shift = 31;

    s[0] = '0';
    s[1] = 'b';

    for (i = 0; i < 32; i++) {
        s[2 + i] = ((value >> shift) & 0b1) ? '1' : '0';
        shift -= 1;
    }

    s[i] = '\0';

    return p;
}

char * uint32_to_binstr_better(uint32_t value) {
    char *s;
    int i;
    int shift = 31;

    s = malloc(64);

    s[0] = '0';
    s[1] = 'b';

    for (i = 0; i < 32; i++) {
        s[2 + i] = ((value >> shift) & 0b1) ? '1' : '0';
        shift -= 1;
    }

    s[2 + i] = '\0';

    return s;
}

void uint32_to_binstr(uint32_t value, char *s) {
    int i;
    int shift = 31;

    s[0] = '0';
    s[1] = 'b';

    for (i = 0; i < 32; i++) {
        s[2 + i] = ((value >> shift) & 0b1) ? '1' : '0';
        shift -= 1;
    }

    s[2 + i] = '\0';
}

int main(int argc, char **argv) {
    char s[64];

    uint32_to_binstr(44, s);

    printf("uint32_to_binstr(44) = %s\n", s);

    return 0;
}
