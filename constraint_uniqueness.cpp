#include "constraint_uniqueness.h"
#include "mainwindow.h"
#include <vector>

ConstraintUniqueness::ConstraintUniqueness(unsigned line) :
    line(line)
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

constraint ConstraintUniqueness::toC()
{
    int gridSize = (int) MainWindow::getInstance()->getGridSize();
    int gridSizeFac = 1;
    //fractorial
    for (unsigned i = 2; i <= gridSize; ++i)
        gridSizeFac *= i;

    int sizeOfResult = sizeof(int)*(gridSizeFac*8-4);
    int *array = (int*) malloc(sizeOfResult);

    int offset = 0;
    for (unsigned i1 = 0; i1 < gridSize; ++i1)
        for (unsigned i2 = 1; i2 < gridSize; ++i2) {
            if (i1 == i2)
                continue;
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
            *(array+offset) = i1;
            //itemVertical.y
            ++offset;
            *(array+offset) = line;
            //itemVertical.x
            ++offset;
            *(array+offset) = i2;
            //itemVertical.y
            ++offset;
            *(array+offset) = line;

            ++offset;
        }

    return &create_constraint(&compareDifference, gridSizeFac*2-1, array);
}

ConstraintUniqueness::operator QString() const
{
    return "Row and column "+QString::number(line)+" must be unique.";
}
