#ifndef BT_H
#define BT_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/timeb.h>

unsigned iterationsCpt, constraintsCpt;
struct timeb start, stop;

bool backtrack();
bool is_consistant();

#endif // BT_H
