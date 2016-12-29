#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "grid.h"

class Constraint
{
public:
    virtual bool eval(Grid& grid) = 0;
    virtual operator QString() const = 0;
};

#endif // CONSTRAINT_H
