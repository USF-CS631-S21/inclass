#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LEN 32
#define STR_LEN 4096


int sum_array_c(int *array, int len);
int sum_array_s(int *array, int len);
int sum_array2_s(int *array, int len);


void gen_array_str(int array[], int len, char *outstr) {
    int i;
    char numstr[STR_LEN];

    *outstr = '\0';
    strncat(outstr, "[", STR_LEN);

    for (i = 0; i < len; i += 1) {
        snprintf(numstr, STR_LEN, "%d", array[i]);
        strncat(outstr, numstr, STR_LEN);
        if ((i + 1) != len) {
            strncat(outstr, ",", STR_LEN);
        }
    }
    strncat(outstr, "]",STR_LEN);
}

void sum_array_test(int array[], int len) {
    int r;
    char arrstr[4096];

    gen_array_str(array, len, arrstr);

    r = sum_array_c(array, len);
    printf("sum_array_c(%s, %d) = %d\n", arrstr, len, r);

    r = sum_array_s(array, len);
    printf("sum_array_s(%s, %d) = %d\n", arrstr, len, r);

    r = sum_array2_s(array, len);
    printf("sum_array2_s(%s, %d) = %d\n", arrstr, len, r);


}

void args_get_array(char **argv, int a[], int *n) {
    int i;
    
    *n = atoi(argv[2]);
    for (i = 0; i < *n; i++) {
        a[i] = atoi(argv[3 + i]);
    }
}

int main(int argc, char **argv) {
    int n;
    int a[4096];

    if (argc == 1) {
        printf("usage: main <prog> [<arg1> ...]\n");
        exit(-1);
    }

    if (strncmp(argv[1], "sum_array", CMD_LEN) == 0) {
        args_get_array(argv, a, &n);
        sum_array_test(a, n);
    }

    return 0;
}
