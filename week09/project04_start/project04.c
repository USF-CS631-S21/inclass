#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "armemu.h"

#define CMD_LEN 32
#define STR_LEN 4096

/* Verbose support */
extern bool g_verbose;

/* Globals to control dynamic analysis and cache simulation */
extern bool g_analysis;
extern int g_cache_type;
extern int g_cache_size;

int max3_c(int a0, int a1, int a2);
int max3_s(int a0, int a1, int a2);

int find_max_c(int *array, int len);
int find_max_s(int *array, int len);

int fib_rec_c(int n);
int fib_rec_s(int n);

void stolower_c(char *s);
void stolower_s(char *s);

char *substr_c(char *s1, char *s2);
char *substr_s(char *s1, char *s2);

int matches_c(char *s1, char *s2);
int matches_s(char *s1, char *s2);

void merge_c(int a[], int i, int j, int aux[]);
void merge_s(int a[], int i, int j, int aux[]);

void merge_sort_c(int a[], int i, int j, int aux[]);
void merge_sort_s(int a[], int i, int j, int aux[]);


void print_stats(struct arm_state *asp);

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

void max3_test(int a0, int a1, int a2) {
    int r;
    struct arm_state state;

    r = max3_c(a0, a1, a2);
    printf("max3_c(%d, %d, %d) = %d\n", a0, a1, a2, r);

    r = max3_s(a0, a1, a2);
    printf("max3_s(%d, %d, %d) = %d\n", a0, a1, a2, r);

    armemu_init(&state, (uint32_t *) max3_s, a0, a1, a2, 0);
    r = armemu(&state);
    printf("max3_e(%d, %d, %d) = %d\n", a0, a1, a2, r);
    print_stats(&state);
}

void find_max_test(int array[], int len) {
    int r;
    char arrstr[4096];
    struct arm_state state;

    gen_array_str(array, len, arrstr);

    r = find_max_c(array, len);
    printf("find_max_c(%s, %d) = %d\n", arrstr, len, r);

    r = find_max_s(array, len);
    printf("find_max_s(%s, %d) = %d\n", arrstr, len, r);

    armemu_init(&state, (uint32_t *) find_max_s, 
                (uint32_t) array, (uint32_t) len, 0, 0);
    r = armemu(&state);
    printf("find_max_e(%s, %d) = %d\n", arrstr, len, r);
    print_stats(&state);
}

void fib_rec_test(int n) {
    int r;
    struct arm_state state;

    r = fib_rec_c(n);
    printf("fib_rec_c(%d) = %d\n", n, r);

    r = fib_rec_s(n);
    printf("fib_rec_s(%d) = %d\n", n, r);

    armemu_init(&state, (uint32_t *) fib_rec_s, n, 0, 0, 0);
    r = armemu(&state);
    printf("fib_rec_e(%d) = %d\n", n, r);
    print_stats(&state);
}

void stolower_test(char *s) {
    char s2[STR_LEN];
    struct arm_state state;

    strncpy(s2, s, STR_LEN - 1);
    stolower_c(s2);
    printf("stolower_c(%s) = %s\n", s, s2);

    strncpy(s2, s, STR_LEN - 1);
    stolower_s(s2);
    printf("stolower_s(%s) = %s\n", s, s2);

    strncpy(s2, s, STR_LEN - 1);
    armemu_init(&state, (uint32_t *) stolower_s, (uint32_t) s2, 0, 0, 0);
    armemu(&state);
    printf("stolower_e(%s) = %s\n", s, s2);
    print_stats(&state);
}

char *substr_test(char *s1, char *s2) {
    char *p;
    int found, index;
    struct arm_state state;

    found = 0;
    index = 0;
    p = substr_c(s1, s2);
    if (p !=  0) {
        found = 1;
        index = (int) (p - s1);
    }
    printf("substr_c(%s, %s) = %d %d\n", s1, s2, found, index);

    found = 0;
    index = 0;
    p = substr_s(s1, s2);
    if (p != 0) {
        found = 1;
        index = (int) (p - s1);
    }
    printf("substr_s(%s, %s) = %d %d\n", s1, s2, found, index);

    found = 0;
    index = 0;
    armemu_init(&state, (uint32_t *) substr_s, (uint32_t) s1, (uint32_t) s2, 0, 0);
    p = (char *) armemu(&state);
    if (p != 0) {
        found = 1;
        index = (int) (p - s1);
    }
    printf("substr_e(%s, %s) = %d %d\n", s1, s2, found, index);
    print_stats(&state);
}

void matches_test(char *s1, char *s2) {
    int r;
    struct arm_state state;

    r = matches_c(s1, s2);
    printf("matches_c(%s, %s) = %d\n", s1, s2, r);

    r = matches_s(s1, s2);
    printf("matches_s(%s, %s) = %d\n", s1, s2, r);

    armemu_init(&state, (uint32_t *) matches_s, (uint32_t) s1, (uint32_t) s2, 0, 0);
    r = armemu(&state);
    printf("matches_e(%s, %s) = %d\n", s1, s2, r);
    print_stats(&state);
}

void merge_test(int array[], int len) {
    int i;
    char arrstr1[4096];
    char arrstr2[4096];
    int acopy[4096];
    int aux[4096];
    struct arm_state state;

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    merge_c(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_c(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    merge_s(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_s(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    armemu_init(&state, (uint32_t *) merge_s,
                (uint32_t) acopy, (uint32_t) 0, (uint32_t) (len - 1), (uint32_t) aux);
    armemu(&state);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_e(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);
    print_stats(&state);
}

void merge_sort_test(int array[], int len) {
    int i;
    char arrstr1[4096];
    char arrstr2[4096];
    int acopy[4096];
    int aux[4096];
    struct arm_state state;
    
    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    merge_sort_c(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_sort_c(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    merge_sort_s(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_sort_s(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    armemu_init(&state, (uint32_t *) merge_sort_s,
                (uint32_t) acopy, (uint32_t) 0, (uint32_t) (len - 1), (uint32_t) aux);
    armemu(&state);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_sort_e(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);
    print_stats(&state);
}

void args_get_array(int i, char **argv, int a[], int *n) {
    int j;

    *n = atoi(argv[i]);
    i += 1;
    for (j = 0; j < *n; j++) {
        a[j] = atoi(argv[j + i]);
    }
}

int parse_args(int argc, char **argv) {
    int i = 1;

    while (i < argc) {
        if (argv[i][0] != '-') {
            /* Done with optional parameters */
            break;
        } else if (argv[i][0] == '-' && argv[i][1] == 'v') {
            g_verbose = true;
            i += 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'a') {
            g_analysis = true;
            i += 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 'd' && argv[i][2] == 'm') {
            i += 1;
            g_cache_type = 0;
            g_cache_size = atoi(argv[i]);
            i += 1;
        } else if (argv[i][0] == '-' && argv[i][1] == 's' && argv[i][2] == 'a') {
            i += 1;
            g_cache_type = 1;
            g_cache_size = atoi(argv[i]);
            i += 1;
        }
    }

    return i;
}

void print_stats(struct arm_state *asp) {
    if (g_analysis) {
        armemu_print(asp);
    }
    if (asp->cache_on) {
        cache_print(asp);
    }
}

int main(int argc, char **argv) {
    int i;
    int n;
    int a[4096];

    if (argc == 1) {
        printf("usage: project04 [-a] [-dm <size> | -sa <size>] <prog> [<arg1> ...]\n");
        exit(-1);
    }

    i = parse_args(argc, argv);
    
    if (strncmp(argv[i], "max3", CMD_LEN) == 0) {
        max3_test(atoi(argv[i + 1]), atoi(argv[i + 2]), atoi(argv[i + 3]));
    } else if (strncmp(argv[i], "find_max", CMD_LEN) == 0) {
        args_get_array(i + 1, argv, a, &n);
        find_max_test(a, n);
    } else if (strncmp(argv[i], "fib_rec", CMD_LEN) == 0) {
        fib_rec_test(atoi(argv[i + 1]));
    } else if (strncmp(argv[i], "stolower", CMD_LEN) == 0) {
        stolower_test(argv[i + 1]);
    } else if (strncmp(argv[i], "substr", CMD_LEN) == 0) {
        substr_test(argv[i + 1], argv[i + 2]);
    } else if (strncmp(argv[i], "matches", CMD_LEN) == 0) {
        matches_test(argv[i + 1], argv[i + 2]);
    } else if (strncmp(argv[i], "merge", CMD_LEN) == 0) {
        args_get_array(i + 1, argv, a, &n);
        merge_test(a, n);
    } else if (strncmp(argv[i], "merge_sort", CMD_LEN) == 0) {
        args_get_array(i + 1, argv, a, &n);
        merge_sort_test(a, n);
    }
    
    return 0;
}
