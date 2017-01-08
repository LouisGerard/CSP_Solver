#ifndef AI_H
#define AI_H

#include "grid.h"
#include "constraint.h"
#include "heuristic.h"
#include <vector>

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
                        int & domains[][],
                        int & domSizes[]);

private:
    Grid const * base;
    std::vector<Constraint*> constraints;
    Heuristic* heuristic;
};

#endif // AI_H
