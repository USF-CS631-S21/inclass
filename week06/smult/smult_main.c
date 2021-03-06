#include <stdio.h>
#include <string.h>

#define STR_LEN 4096

void smult_c(int *array, int len, int s);
void smult_s(int *array, int len, int s);


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

int main(int argc, char **argv) {
    int a[] = {1, 2, 3, 4, 5};
    int ac[5];
    int i;
    int s = 3;
    char arrstr_in[4096];
    char arrstr_out[4096];
    
    for (i = 0; i < 5; i += 1) {
        ac[i] = a[i];
    }

    gen_array_str(ac, 5, arrstr_in);
    smult_c(ac, 5, s);
    gen_array_str(ac, 5, arrstr_out);
    printf("smult_c(%s, 5, %d) = %s\n", arrstr_in, s, arrstr_out);

    for (i = 0; i < 5; i += 1) {
        ac[i] = a[i];
    }

    gen_array_str(ac, 5, arrstr_in);
    smult_s(ac, 5, s);
    gen_array_str(ac, 5, arrstr_out);
    printf("smult_s(%s, 5, %d) = %s\n", arrstr_in, s, arrstr_out);

    return 0;
}
