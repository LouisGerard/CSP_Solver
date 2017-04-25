#include "constraint_uniqueness.h"
#include "mainwindow.h"
#include <vector>

#include <QDebug>

ConstraintUniqueness::ConstraintUniqueness(unsigned line, unsigned gridSize /*=0*/) :
    line(line),
    gridSize(gridSize)
{}

bool ConstraintUniqueness::eval(Grid& grid)
{
    std::vector<unsigned> hashHorizontal(grid.size());
    std::vector<unsigned> hashVertical(grid.size());
    for (unsigned x = 0; x < hashHorizontal.size(); ++x) {
        for (unsigned y = 0; y < hashVertical.size(); ++y) {
            unsigned valueHor = grid.get(x, line);
            if (hashHorizontal[valueHor] != 0)
                return false;
            hashHorizontal[valueHor] = 1;

            unsigned valueVer = grid.get(line, y);
            if (hashVertical[valueVer] != 0)
                return false;
            hashVertical[valueVer] = 1;
        }
    }
    return true;
}

constraint * ConstraintUniqueness::toC()
{
    if (gridSize == 0)
        gridSize = (int) MainWindow::getInstance()->getGridSize();
    unsigned size = 0;
    for (unsigned i = 1; i < gridSize; ++i)
        size += i;
    size *= 2;

    int *array = (int*) malloc(sizeof(int)*(size*4));

    int offset = 0;
    for (unsigned i1 = 0; i1 < gridSize; ++i1)
        for (unsigned i2 = i1+1; i2 < gridSize; ++i2) {
            //itemHorizontal.x
            *(array+offset) = i1;
            //itemHorizontal.y
            ++offset;
            *(array+offset) = line;
            //itemHorizontal.x
            ++offset;
            *(array+offset) = i2;
            //itemHorizontal.y
            ++offset;
            *(array+offset) = line;

            //itemVertical.x
            ++offset;
            *(array+offset) = line;
            //itemVertical.y
            ++offset;
            *(array+offset) = i1;
            //itemVertical.x
            ++offset;
            *(array+offset) = line;
            //itemVertical.y
            ++offset;
            *(array+offset) = i2;

            ++offset;
        }

    return create_constraint(&compareDifference, size, array);
}

ConstraintUniqueness::operator QString() const
{
    return "Row and column "+QString::number(line)+" must be unique.";
}
