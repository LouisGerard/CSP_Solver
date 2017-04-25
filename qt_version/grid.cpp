#include "grid.h"
#include "item.h"
#include <QDebug>
#include <vector>
#include <string>

Grid::Grid(unsigned size)
{
    for(unsigned i = 0; i < size; ++i) {
        std::vector<Item> row;
        row.resize(size);
        grid.push_back(row);
    }
    qDebug() << "Grid created, size : " << this->size();
}

Grid::Grid(int *gridC, unsigned gridSize)
{
    grid.resize(gridSize);
    for (unsigned x = 0; x < gridSize; ++x) {
        grid[x].resize(gridSize);
        for (unsigned y = 0; y < gridSize; ++y) {
            unsigned offset = y*gridSize+x;
            grid[x][y] = *(gridC+offset);
        }
    }
}

Grid::Grid(const Grid & cpy)
{
    grid = cpy.grid;
}

Item Grid::get(unsigned x, unsigned y) const
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

unsigned Grid::size() const
{
    return grid.size();
}

int *Grid::toC() const
{
    int* result = (int*) malloc(sizeof(int)*grid.size()*grid.size());
    for (unsigned y = 0; y < grid.size(); ++y)
        for (unsigned x = 0; x < grid.size(); ++x)
            *(result+grid.size()*y+x) = (int) grid[x][y];

    return result;
}

Grid::operator QString() const
{
    QString print = "";
    for (unsigned y = 0; y < grid.size(); ++y) {
        for (unsigned x = 0; x < grid.size(); ++x) {
            print += QString::number(grid[x][y]) + ", ";
        }
        print += "\n";
    }
    return print;
}
