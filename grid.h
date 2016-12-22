#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid
{
public:
    Grid(unsigned size);
    unsigned get(unsigned x, unsigned y);
    bool assign(unsigned x, unsigned y, unsigned value);
    unsigned size();
private:
    std::vector< std::vector<unsigned> > grid;
};

#endif // GRID_H
