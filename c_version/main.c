#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "backtrack.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("missing path");
        exit(1);
    }

    setup(argv[1]);
    if (backtrack())
        show_grid();
    else
        printf("No result !");
    return 0;
}
