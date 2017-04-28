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

    int domainSizes[nbVars+1][grid_size*grid_size];
    for (unsigned i = 0; i <= nbVars; ++i) {
        for (unsigned j = 0; j < grid_size*grid_size; ++j)
            domainSizes[i][j] = grid_size;
    }


    printf("Searching...\n");
    ftime(&start);
    iterations_cpt = grid_size*grid_size;
    constraints_cpt = 0;

    for (int i = 0; i < grid_size*grid_size; ++i)
        if (*(grid+i) != 0)
            filter_domains(i, domains, domainSizes[stackTop+1]);

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

        int domainSizesCpy[grid_size*grid_size];

        //eval domain
        for (; domainsOffsets[stackTop] < domainSizes[stackTop][currentItem]; ++domainsOffsets[stackTop]) {
            *(grid+currentItem) = *(domains[currentItem]+domainsOffsets[stackTop]);

            memcpy(&domainSizes[stackTop], &domainSizes[stackTop+1], grid_size*grid_size*sizeof(int));

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

            for (unsigned d = 0; d < domSizes[linkedItem]; ++d) {
                ++constraints_cpt;
                *linkedVal = domains[linkedItem][d];
                if (!constraints[c]->operation(*val1, *val2)) {
                    //remove value from domain (swap)
                    int temp = domains[linkedItem][d];
                    domains[linkedItem][d] = domains[linkedItem][domSizes[linkedItem]-1];
                    domains[linkedItem][domSizes[linkedItem]-1] = temp;
                    --domSizes[linkedItem];
                    --d;
                }
            }
            *linkedVal = 0;

            if (domSizes[linkedItem] == 0) {
                return false;
            }
        }
    }
    return true;
}



bool forward_checking_optimized()
{
    printf("Optimized called\n");

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

    //heuristic -> sort by nb linked constraints
    //count nb constraints
    unsigned nb_constraints[grid_size*grid_size];
    for (unsigned i = 0; i < grid_size*grid_size; ++i)
        nb_constraints[i] = 0;

    for (unsigned c = 0; c < constraints_size; ++c) {
        for (unsigned a = 0; a < constraints[c]->size; ++a) {
            unsigned x1 = *(constraints[c]->array+a*4);
            unsigned y1 = *(constraints[c]->array+a*4+1);
            unsigned x2 = *(constraints[c]->array+a*4+2);
            unsigned y2 = *(constraints[c]->array+a*4+3);
            int item1 = y1*grid_size+x1;
            int item2 = y2*grid_size+x2;
            ++nb_constraints[item1];
            ++nb_constraints[item2];
        }
    }

    //evidences
    int evidences[grid_size*grid_size];
    unsigned evidences_size = 0;
    bool is_evident[grid_size*grid_size];

    //todo find name (ideas : sorter)
    unsigned aze[5];
    unsigned aze_size = 0;

    //vars
    int varStack[grid_size*grid_size];
    int stackTop = -1;
    for (int* item = grid; item-grid < grid_size*grid_size; ++item) {
        is_evident[item-grid] = false;
        if (*item == 0) {
            ++stackTop;

            //sort
            bool index_assigned = false;
            unsigned aze_index;
            for (unsigned i = 0; i < aze_size; ++i) {
                if (index_assigned) {
                    ++aze[i];
                    continue;
                }
                unsigned stack_pos = aze[i];
                if (nb_constraints[item-grid] <= nb_constraints[varStack[stack_pos]]) {
                    aze_index = stack_pos;
                    if (nb_constraints[item-grid] != nb_constraints[varStack[aze[i]]]) {
                        unsigned temp[aze_size-i];
                        memcpy(&temp[0], &aze[i], (aze_size-i)*sizeof(unsigned));
                        memcpy(&aze[i+1], &temp[0], (aze_size-i)*sizeof(unsigned));
                        ++aze_size;
                    }
                    index_assigned = true;
                }
            }
            if (!index_assigned) {
                aze_index = stackTop;
                aze[aze_size++] = stackTop;
            }
            else {
                int temp[stackTop-aze_index];
                memcpy(&temp[0], &varStack[aze_index], (stackTop-aze_index)*sizeof(int));
                memcpy(&varStack[aze_index+1], &temp[0], (stackTop-aze_index)*sizeof(int));
            }

            varStack[aze_index] = item-grid;
        }
    }

    //sizes
    unsigned nbVars = stackTop + 1;

    int domainSizes[nbVars+1][grid_size*grid_size];
    for (unsigned i = 0; i <= nbVars; ++i) {
        for (unsigned j = 0; j < grid_size*grid_size; ++j)
            domainSizes[i][j] = grid_size;
    }

    printf("Searching...\n");
    ftime(&start);
    iterations_cpt = grid_size*grid_size;
    constraints_cpt = 0;

    for (int i = 0; i < grid_size*grid_size; ++i)
        if (*(grid+i) != 0)
            filter_domains_with_evidences(i, domains, domainSizes[stackTop + 1], evidences, &evidences_size, is_evident);

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
        if (evidences_size > 0) {
            show_grid();
            printf("Domains : \n");
            for (unsigned i = 0; i < grid_size * grid_size; ++i) {
                printf("%d: ", i);
                for (unsigned d = 0; d < grid_size; ++d) {
                    printf("%d,", domains[i][d]);
                    if (d == domainSizes[stackTop + 1][i] - 1)
                        printf("|");
                }
                printf("\n");
            }
            printf("Evidences : ");
            for (unsigned i = 0; i < evidences_size; ++i) {
                printf("%d,", evidences[i]);
            }
            printf("\n");
            printf("\n");
        }

        //eval domain
        for (; domainsOffsets[stackTop] < domainSizes[stackTop][currentItem]; ++domainsOffsets[stackTop]) {
            *(grid+currentItem) = *(domains[currentItem]+domainsOffsets[stackTop]);

            memcpy(&domainSizes[stackTop], &domainSizes[stackTop+1], grid_size*grid_size*sizeof(int));

            if (filter_domains_with_evidences(currentItem,
                                domains,
                                domainSizes[stackTop],
                                evidences,
                                &evidences_size,
                                is_evident)) {
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

bool filter_domains_with_evidences(int item,
                    int ** domains,
                    int * domSizes,
                    int *evidences,
                    unsigned *evidences_size,
                    bool *is_evident)
{
    int *linkedVal;
    int evidences_cpy[grid_size*grid_size];
    memcpy(&evidences_cpy[0], &evidences[0], *evidences_size*sizeof(int));
    unsigned evidences_cpy_size = *evidences_size;
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

            for (unsigned d = 0; d < domSizes[linkedItem]; ++d) {
                ++constraints_cpt;
                *linkedVal = domains[linkedItem][d];
                if (!constraints[c]->operation(*val1, *val2)) {
                    //remove value from domain (swap)
                    int temp = domains[linkedItem][d];
                    domains[linkedItem][d] = domains[linkedItem][domSizes[linkedItem]-1];
                    domains[linkedItem][domSizes[linkedItem]-1] = temp;
                    --domSizes[linkedItem];
                    --d;
                }
            }
            *linkedVal = 0;

            if (domSizes[linkedItem] == 0) {
                return false;
            }

            if (domSizes[linkedItem] == 1 && !is_evident[linkedItem]) {
                is_evident[linkedItem] = true;
                evidences_cpy[evidences_cpy_size++] = linkedItem;
            }
        }
    }
    memcpy(&evidences[0], &evidences_cpy[0], evidences_cpy_size*sizeof(int));
    *evidences_size = evidences_cpy_size;
    return true;
}
