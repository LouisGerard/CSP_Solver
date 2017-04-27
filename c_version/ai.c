#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include "ai.h"
#include "csp.h"

bool backtrack()
{
    printf("BT called\n");

    //vars
    int varStack[grid_size*grid_size];
    int stackTop = -1;

    //domains
    //can be replaced by an array of counters
    int* domains[grid_size*grid_size];
    int* defaultDomain = (int*) malloc(grid_size*sizeof(int));
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
    iterations_cpt = 0;
    constraints_cpt = 0;
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

        ++iterations_cpt;
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
            ++constraints_cpt;
            if (!constraints[c]->operation(item1, item2))
                return false;
        }
    }
    return true;
}



bool forward_checking()
{
    printf("FC called\n");

    //domains
    int* defaultDomain = (int*) malloc(grid_size*sizeof(int));
    for (int i = 1; i <= grid_size; ++i)
        *(defaultDomain+i-1) = i;

    int* domains[grid_size*grid_size];
    int domainsOffsets[grid_size*grid_size];
    for (unsigned i = 0; i < grid_size*grid_size; ++i) {
        domains[i] = (int*) malloc(grid_size*sizeof(int));
        memcpy(domains[i], defaultDomain, grid_size*sizeof(int));
        domainsOffsets[i] = 0;
    }

    //vars
    int varStack[grid_size*grid_size];
    int stackTop = -1;
    for (int* item = grid; item-grid < grid_size*grid_size; ++item) {
        if (*item == 0) {
            varStack[++stackTop] = item-grid;
        }
    }

    //sizes
    unsigned nbVars = stackTop + 1;

    int domainSizes[grid_size*grid_size][grid_size*grid_size];
    for (unsigned i = 0; i < grid_size*grid_size; ++i) {
        for (unsigned j = 0; j < grid_size*grid_size; ++j)
            domainSizes[i][j] = grid_size;
    }


    printf("Searching...\n");
    ftime(&start);
    iterations_cpt = grid_size*grid_size;
    constraints_cpt = 0;

    for (int i = 0; i < grid_size*grid_size; ++i)
        if (*(grid+i) != 0)
            filter_domains(i, domains, domainSizes[stackTop]);  //todo avoid big fuck up
//
/*    show_grid();
    printf("\n");
    printf("Domain : ");
    for (unsigned i = 0; i < grid_size*grid_size; ++i) {
        for (unsigned d = 0; d < domainSizes[stackTop][i]; ++d) {
            printf("%d,", domains[i][d]);
        }
        printf("\n");
    }
    printf("\n");*/

    while (true) {
        continue_while:

        if (stackTop == -1) {
            ftime(&stop);
            for (unsigned i = 0; i < grid_size*grid_size; ++i)
                free(domains[i]);
            return true;
        }
        if (stackTop == nbVars) {
            ftime(&stop);
            for (unsigned i = 0; i < grid_size*grid_size; ++i)
                free(domains[i]);
            return false;
        }

        ++iterations_cpt;
        unsigned currentItem = varStack[stackTop];
//
       /* if (currentItem == 24 || currentItem == 18) {
            show_grid();
            printf("\n");
        }*/
//
        /*if (currentItem == 24 || currentItem == 18) {
            printf("Domain :\n");
            for (unsigned i = 0; i < grid_size*grid_size; ++i) {
                printf("%d:", i);
                for (unsigned d = 0; d < domainSizes[stackTop][i]; ++d) {
                    printf("%d,", domains[i][d]);
                }
                printf("\n");
            }
            printf("\n");
        }*/

        //eval domain
        for (; domainsOffsets[stackTop] < domainSizes[stackTop][currentItem]; ++domainsOffsets[stackTop]) {
            *(grid+currentItem) = *(domains[currentItem]+domainsOffsets[stackTop]);

            if (stackTop != nbVars-1)
                memcpy(&domainSizes[stackTop], &domainSizes[stackTop+1], grid_size*grid_size*sizeof(int));


//
            /*if (currentItem == 15 && iterations_cpt == 626) {
                show_grid();
                printf("Loop s+1 : ");
                for (unsigned d = 0; d < grid_size; ++d) {
                    printf("%d,", domains[9][d]);
                    if (d == domainSizes[stackTop+1][9]-1)
                        printf("|");
                }
                printf("\n\n");
            }*/

            if (filter_domains(currentItem,
                                domains,
                                domainSizes[stackTop])) {
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

bool filter_domains(int item,
                    int ** domains,
                    int * domSizes)
{
    int *linkedVal;
    for (unsigned c = 0; c < constraints_size; ++c) {
        for (unsigned a = 0; a < constraints[c]->size; ++a) {
            unsigned x1 = *(constraints[c]->array+a*4);
            unsigned y1 = *(constraints[c]->array+a*4+1);
            unsigned x2 = *(constraints[c]->array+a*4+2);
            unsigned y2 = *(constraints[c]->array+a*4+3);
            int item1 = y1*grid_size+x1;
            int item2 = y2*grid_size+x2;
            int linkedItem;
            int *val1 = grid+item1;
            int *val2 = grid+item2;

            if (item != item1) {
                if (item != item2)
                    continue;
                linkedItem = item1;
                linkedVal = val1;
            }
            else {
                linkedItem = item2;
                linkedVal = val2;
            }

            if (*linkedVal != 0)
                continue;
//
            /*if (item == 15 && linkedItem == 9 && iterations_cpt == 626) {
                for (unsigned y = 0; y < grid_size; ++y) {
                    for (unsigned x = 0; x < grid_size; ++x) {
                        if (y*grid_size+x == linkedItem)
                            printf("|");
                        else
                            printf(" ");
                        printf("%d", grid[y*grid_size+x]);
                    }
                    printf("\n");
                }
                printf("Before : ");
                for (unsigned d = 0; d < grid_size; ++d) {
                    printf("%d,", domains[linkedItem][d]);
                    if (d == domSizes[linkedItem]-1)
                        printf("|");
                }
                printf("\n");
            }*/

            for (unsigned d = 0; d < domSizes[linkedItem]; ++d) {
                ++constraints_cpt;
                *linkedVal = domains[linkedItem][d];
                if (!constraints[c]->operation(*val1, *val2)) {
                    //remove value from domain
                    int temp = domains[linkedItem][d];
                    domains[linkedItem][d] = domains[linkedItem][domSizes[linkedItem]-1];
                    domains[linkedItem][domSizes[linkedItem]-1] = temp;
                    --domSizes[linkedItem];
                    --d;
                }
            }
            *linkedVal = 0;

//
            /*if (item == 15 && linkedItem == 9 && iterations_cpt == 626) {
                printf("After : ");
                for (unsigned d = 0; d < grid_size; ++d) {
                    printf("%d,", domains[linkedItem][d]);
                    if (d == domSizes[linkedItem]-1)
                        printf("|");
                }
                printf("\n\n");
            }*/

            if (domSizes[linkedItem] == 0)
                return false;
        }
    }
    return true;
}