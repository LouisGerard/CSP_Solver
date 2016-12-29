#include "assignment.h"

#include "grid.h"
#include "constraint.h"
#include <vector>

Assignment::Assignment(const Grid* grid, std::vector<Constraint*> constraints) :
    grid(*grid),
    constraints(constraints)
{}

bool Assignment::isConsistent()
{
    for (Constraint* constraint : constraints)
        if (!constraint->eval(grid))
            return false;
    return true;
}

void Assignment::assign(unsigned x, unsigned y, unsigned domainIndex)
{
    //todo
    unsigned assignedValue = grid.get(x, y).getDomain()[domainIndex];
    grid.assign(x, y, assignedValue);
}

Grid Assignment::getGrid() const
{
    return grid;
}
