#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    unsigned int i = 0;
    unsigned int j = 0;
    char *label = NULL;

    if (argc == 2) {
        label = argv[1];
    }

    while (1) {
        if (label) {
            printf(1, "[%s] i = %d\n", label, i);
        } else {
            printf(1, "i = %d\n", i);
        }

        /* busy wait */
        for (j = 0; j < 10000000; j++);
        i = i + 1;
    }

    exit();
}

