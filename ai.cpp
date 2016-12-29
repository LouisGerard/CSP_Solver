#include "ai.h"

#include "grid.h"
#include "constraint.h"
#include <vector>

AI::AI(Grid * base, std::vector<Constraint*> constraints) :
    base(base),
    constraints(constraints)
{}

Grid AI::BT()
{
    Grid assignment(*base);
    for (unsigned x = 0; x < assignment.size(); ++x) {
        for (unsigned y = 0; y < assignment.size(); ++y) {
            if (assignment.get(x, y) != 0)
                continue;
            std::vector<unsigned> domain = assignment.get(x, y).getDomain();
            for (unsigned i = 0; i < domain.size(); ++i) {
                assignment.assign(x, y, domain[i]);
                if (isConsistent(&assignment))
                    break;
            }
        }
    }
    return assignment;
}

bool AI::isConsistent(Grid *assignment)
{
    for (Constraint* constraint : constraints)
        if (!constraint->eval(assignment))
            return false;
    return true;
}

