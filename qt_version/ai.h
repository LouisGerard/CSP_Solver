#ifndef AI_H
#define AI_H

#include "grid.h"
#include "constraint.h"
#include "heuristic.h"
#include <vector>
#include <sys\timeb.h>

class AI
{
public:
    AI(Grid * base, std::vector<Constraint*> constraints, Heuristic* heuristic);
    Grid BackTrack();
    int* BackTrackC();
    Grid ForwardChecking();
    int* ForwardCheckingC();
    int* ForwardCheckingCOptimized();

    bool isConsistantC(int* grid, constraint* constraints[], unsigned consSize, unsigned gridSize);
    bool filterDomainsC(int item,
                        int *grid,
                        constraint *constraints[],
                        unsigned consSize,
                        unsigned gridSize,
                        int ** domains,
                        int * domSizes);

    struct timeb getStart() const;

    struct timeb getStop() const;

    unsigned getIterationsCpt() const;

    unsigned getConstraintsCpt() const;

private:
    Grid const * base;
    std::vector<Constraint*> constraints;
    Heuristic* heuristic;

    struct timeb start, stop;
    unsigned iterationsCpt = 0;
    unsigned constraintsCpt = 0;
};

#endif // AI_H
