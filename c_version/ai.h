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

#endif // AI_H
