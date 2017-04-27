#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csp.h"
#include "ai.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("missing path");
        exit(1);
    }

    setup(argv[1]);
    if (forward_checking_optimized())
        show_grid();
    else
        printf("No result !\n");
    printf("Time : %dms\n", (int) (1000.0 * (stop.time - start.time)
                                 + (stop.millitm - start.millitm)));
    printf("Iterations : %d\n", iterations_cpt);
    printf("Constraints : %d\n", constraints_cpt);
    return 0;
}
