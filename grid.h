#ifndef GRID_H
#define GRID_H

#include "item.h"
#include <vector>
#include <QString>

class Grid
{
public:
    Grid(unsigned size);
    Grid(int* gridC, unsigned gridSize);
    Grid(const Grid & cpy);
    Item get(unsigned x, unsigned y) const;
    bool assign(unsigned x, unsigned y, unsigned value);
    unsigned size() const;
    operator QString() const;
    int* toC() const;
private:
    std::vector< std::vector<Item> > grid;
};

#endif // GRID_H
