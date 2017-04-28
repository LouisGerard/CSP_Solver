#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/timeb.h>

unsigned iterations_cpt, constraints_cpt;
struct timeb start, stop;

bool backtrack();
bool is_consistant();

bool forward_checking();
bool filter_domains(int item,
                    int ** domains,
                    int * domSizes);

bool forward_checking_optimized();
bool filter_domains_with_evidences(int item,
                                   int ** domains,
                                   int * domSizes,
                                   int *evidences,
                                   unsigned *evidences_size,
                                   bool *is_evident);

#endif // AI_H
