#ifndef CONSTRAINT_UNIQUENESS_H
#define CONSTRAINT_UNIQUENESS_H

#include "constraint.h"

class ConstraintUniqueness : public Constraint
{
public:
    ConstraintUniqueness(unsigned line);

    bool eval(Grid& grid);
    operator QString() const;


private:
    unsigned line;
};

#endif // CONSTRAINT_UNIQUENESS_H
