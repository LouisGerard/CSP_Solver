#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "grid.h"

class Constraint
{
public:
    virtual bool eval(Grid& grid) = 0;
    virtual operator QString() const = 0;

    //size | operation | [ item1.x | item1.y | item2.x | item2.y ]
    virtual int* toC() = 0;
};

#endif // CONSTRAINT_H

typedef struct _constraint
{
    typedef bool (*function)(int,int);
    function * operation;
    unsigned size;
    int * array;
} constraint;



bool function1 (int first, int second)
{
}
bool function2 (int first, int second)
{
}

constraint create_constraint (function * f,unsigned size, int * array)
{
    constraint constr;

    constr.operation = f;
    constr.array = array;
    constr.size = size;

    return constr;
}