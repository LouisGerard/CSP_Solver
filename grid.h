#ifndef GRID_H
#define GRID_H

#include "item.h"
#include <vector>
#include <QString>

class Grid
{
public:
    Grid(unsigned size);
    Grid(const Grid & cpy);
    Item get(unsigned x, unsigned y);
    bool assign(unsigned x, unsigned y, unsigned value);
    unsigned size();
    operator QString() const;
private:
    std::vector< std::vector<Item> > grid;
};

#endif // GRID_H
