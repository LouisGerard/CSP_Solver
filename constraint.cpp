#include "constraint.h"


constraint * create_constraint (function f, unsigned size, int * array)
{
    constraint * constr = (constraint*)malloc(sizeof(constraint));

    constr->operation = f;
    constr->array = array;
    constr->size = size;

    return constr;
}
