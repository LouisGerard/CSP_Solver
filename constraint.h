#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "grid.h"
#include <utility>

class Constraint
{
public:
    Constraint(std::pair<unsigned, unsigned> itemSup, std::pair<unsigned, unsigned> itemInf);
    bool eval(Grid grid);


    std::pair<unsigned, unsigned> getItemSup() const;
    void setItemSup(const std::pair<unsigned, unsigned> &value);

    std::pair<unsigned, unsigned> getItemInf() const;
    void setItemInf(const std::pair<unsigned, unsigned> &value);

    operator QString() const;

private:
    std::pair<unsigned, unsigned> itemSup;
    std::pair<unsigned, unsigned> itemInf;
};

#endif // CONSTRAINT_H
