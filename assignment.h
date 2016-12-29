#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "grid.h"
#include "constraint.h"
#include <vector>

class Assignment
{
public:
    Assignment(const Grid* grid, std::vector<Constraint*> constraints);
    bool isConsistent();
    void assign(unsigned x, unsigned y, unsigned domainIndex);

    Grid getGrid() const;

private:
    Grid grid;
    std::vector<Constraint*> constraints;
};

#endif // ASSIGNMENT_H
