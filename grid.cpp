#include "grid.h"

#include <QDebug>
#include <vector>
#include <string>

Grid::Grid(unsigned size)
{
    for(unsigned i = 0; i < size; ++i) {
        std::vector<unsigned> row;
        row.resize(size);
        grid.push_back(row);
    }
    qDebug() << "Grid created, size : " << this->size();
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

unsigned Grid::size()
{
    return grid.size();
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
