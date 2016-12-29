#include "ai.h"

#include "grid.h"
#include "constraint.h"
#include "assignment.h"
#include <vector>

AI::AI(Grid * base, std::vector<Constraint*> constraints) :
    base(base),
    constraints(constraints)
{}

Grid AI::BT()
{
    Assignment assignment(base, constraints);
    for (unsigned x = 0; x < base->size(); ++x) {
        for (unsigned y = 0; y < base->size(); ++y) {
            if (base->get(x, y) != 0)
                continue;
            for (unsigned i = 0; i < base->get(x, y).getDomain().size(); ++i) {
                assignment.assign(x, y, i);
                if (assignment.isConsistent())
                    break;
            }
        }
    }
    return assignment.getGrid();
}

