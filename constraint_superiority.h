#ifndef CONSTRAINT_SUPERIORITY_H
#define CONSTRAINT_SUPERIORITY_H

#include "grid.h"
#include "constraint.h"
#include <utility>

class ConstraintSuperiority : public Constraint
{
public:
    ConstraintSuperiority(std::pair<unsigned, unsigned> itemSup, std::pair<unsigned, unsigned> itemInf);
    bool eval(Grid& grid);
    constraint * toC();


    std::pair<unsigned, unsigned> getItemSup() const;
    void setItemSup(const std::pair<unsigned, unsigned> &value);

    std::pair<unsigned, unsigned> getItemInf() const;
    void setItemInf(const std::pair<unsigned, unsigned> &value);

    operator QString() const;

private:
    std::pair<unsigned, unsigned> itemSup;
    std::pair<unsigned, unsigned> itemInf;
};

inline bool compareSuperiority (unsigned first, unsigned second)
{
    return first > second;
}

#endif // CONSTRAINT_SUPERIORITY_H
