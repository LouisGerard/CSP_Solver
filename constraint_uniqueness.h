#ifndef CONSTRAINT_UNIQUENESS_H
#define CONSTRAINT_UNIQUENESS_H

#include "constraint.h"

class ConstraintUniqueness : public Constraint
{
public:
    ConstraintUniqueness(unsigned line);

    bool eval(Grid& grid);
    operator QString() const;
    constraint * toC();

private:
    unsigned line;
    unsigned gridSize;
};

bool compareDifference (unsigned first, unsigned second)
{
    return first != second;
}

#endif // CONSTRAINT_UNIQUENESS_H
