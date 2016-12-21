#include "grid.h"

#include <QDebug>

Grid::Grid(unsigned size)
{
    unsigned *grid[size];
    for(unsigned i = 0; i < size; ++i) {
        grid[i] = (unsigned*) malloc(size*size*sizeof(unsigned));
        for (unsigned j = 0; j < size; ++j)
            grid[i][j] = 0;
    }
    memcpy(this->grid, grid, sizeof(grid));
    qDebug() << "Grid created, size : " << sizeof(grid)/ sizeof(grid[0]);
}

unsigned Grid::get(unsigned x, unsigned y)
{
    return grid[x][y];
}

bool Grid::assign(unsigned x, unsigned y, unsigned value)
{
    if (grid[x][y] != 0)
        return false;
    grid[x][y] = value;
    return true;
}

unsigned Grid::length()
{
    return sizeof(grid) / sizeof(grid[0]);
}
