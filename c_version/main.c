#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        perror("missing path");
        exit(1);
    }
    char *read;
    size_t read_size = read_file(argv[1], &read);
    parse_grid(read, read_size);
    parse_cons(read, read_size);
    free(read);
    return 0;
}
