#ifndef AI_H
#define AI_H

#include "grid.h"
#include "constraint.h"
#include "heuristic.h"
#include <vector>

class AI
{
public:
    AI(Grid * base, std::vector<Constraint*> constraints, Heuristic heuristic);
    Grid BT();
    Grid FC();

private:
    Grid const * base;
    std::vector<Constraint*> constraints;
    Heuristic heuristic;
};

#endif // AI_H
