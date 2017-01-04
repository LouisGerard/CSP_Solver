#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "grid.h"

//conversion
typedef bool (*function)(unsigned, unsigned);
typedef struct _constraint
{
    function operation;
    unsigned size;
    int * array;
} constraint;

constraint * create_constraint (function f, unsigned size, int * array);

class Constraint
{
public:
    virtual bool eval(Grid& grid) = 0;
    virtual operator QString() const = 0;

    //size | operation | [ item1.x | item1.y | item2.x | item2.y ]
    virtual constraint * toC() = 0;
};

#endif // CONSTRAINT_H
