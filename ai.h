#ifndef AI_H
#define AI_H

#include "grid.h"
#include "constraint.h"
#include <vector>

class AI
{
public:
    AI(Grid * base, std::vector<Constraint*> constraints);
    Grid BT();
    Grid FC();

private:
    bool isConsistent(Grid * assignment);

    Grid const * base;
    std::vector<Constraint*> constraints;
};

#endif // AI_H
