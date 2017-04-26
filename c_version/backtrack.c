#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include "backtrack.h"
#include "common.h"

bool backtrack()
{
    printf("BT called\n");

    //vars
    int varStack[grid_size*grid_size];
    int stackTop = -1;

    //domains
    //can be replaced by an array of counters
    int* domains[grid_size*grid_size];
    int* defaultDomain = (int*) malloc(grid_size);
    for (int i = 1; i <= grid_size; ++i)
        *(defaultDomain+i-1) = i;
    int domainsOffsets[grid_size*grid_size];
    for (unsigned i = 0; i < grid_size*grid_size; ++i)
        domainsOffsets[i] = 0;

    //assign
    for (int* item = grid; item-grid < grid_size*grid_size; ++item) {
        if (*item == 0) {
            varStack[++stackTop] = item-grid;
            domains[stackTop] = (int*) malloc(grid_size*sizeof(int));
            memcpy(domains[stackTop], defaultDomain, grid_size*sizeof(int));
        }
    }

    unsigned nbVars = stackTop + 1;

    printf("Searching...\n");
    ftime(&start);
    iterationsCpt = 0;
    while (true) {
        continue_while:
        if (stackTop == -1) {
            ftime(&stop);
            for (unsigned i = 0; i < nbVars; ++i)
                free(domains[i]);
            return true;
        }
        if (stackTop == nbVars) {
            ftime(&stop);
            for (unsigned i = 0; i < nbVars; ++i)
                free(domains[i]);
            return false;
        }

        ++iterationsCpt;
        unsigned currentItem = varStack[stackTop];

        //eval domain
        for (; domainsOffsets[stackTop] < grid_size; ++domainsOffsets[stackTop]) {
            *(grid+currentItem) = *(domains[stackTop]+domainsOffsets[stackTop]);
            if (is_consistant()) {
                --stackTop;
                goto continue_while;
            }
        }

        //reinit domain
        domainsOffsets[stackTop] = 0;

        //reinit grid
        *(grid+currentItem) = 0;

        ++stackTop;
        ++domainsOffsets[stackTop];
    }
}

bool is_consistant()
{
    for (unsigned c = 0; c < constraints_size; ++c) {
        for (unsigned a = 0; a < constraints[c]->size; ++a) {
            unsigned x1 = *(constraints[c]->array+a*4);
            unsigned y1 = *(constraints[c]->array+a*4+1);
            unsigned x2 = *(constraints[c]->array+a*4+2);
            unsigned y2 = *(constraints[c]->array+a*4+3);
            int item1 = *(grid+y1*grid_size+x1);
            int item2 = *(grid+y2*grid_size+x2);
            ++constraintsCpt;
            if (!constraints[c]->operation(item1, item2))
                return false;
        }
    }
    return true;
}
