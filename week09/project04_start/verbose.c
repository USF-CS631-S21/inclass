/* verbose.c - Implement a logging function for debugging */


#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "armemu.h"

static bool g_verbose;

void verbose_init(bool v) {
    g_verbose = v;
}


void verbose(char *fmt, ...) {
    if (g_verbose) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}
