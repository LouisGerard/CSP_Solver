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

void Assignment::next(unsigned x, unsigned y)
{

}

Grid Assignment::getGrid() const
{
    return grid;
}
