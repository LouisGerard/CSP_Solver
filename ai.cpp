#include "ai.h"

#include "grid.h"
#include "constraint.h"
#include "assignment.h"
#include <utility>
#include <vector>
#include <QDebug>

AI::AI(Grid * base, std::vector<Constraint*> constraints, Heuristic heuristic) :
    base(base),
    constraints(constraints),
    heuristic(heuristic)
{}

Grid AI::BT()
{
    Assignment assignment(base, constraints);
    for (std::pair<unsigned, unsigned> pos = heuristic.next();
         !heuristic.end();
         pos = heuristic.next) {
        if (base->get(pos.first, pos.second) != 0)
            continue;
        for (unsigned i = 0; i < base->get(pos.first, pos.second).getDomain().size(); ++i) {
            assignment.assign(pos.first, pos.second, i);
            if (assignment.isConsistent())
                break;
        }
    }
    return assignment.getGrid();
}

