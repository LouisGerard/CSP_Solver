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

int *ConstraintUniqueness::toC()
{
    int gridSize = (int) MainWindow::getInstance()->getGridSize();
    int gridSizeFac = 1;
    //fractorial
    for (unsigned i = 2; i <= gridSize; ++i)
        gridSizeFac *= i;

    int sizeOfResult = sizeof(int)*(gridSizeFac*8-2);
    int *result = (int*) malloc(sizeOfResult);
    //size
    *result = gridSizeFac*2-1;
    //operation
    *(result+sizeof(int)) = 2;

    int offset = sizeof(int)*2;
    //items
    for (unsigned i1 = 0; i1 < gridSize; ++i1)
        for (unsigned i2 = 1; i2 < gridSize; ++i2) {
            if (i1 == i2)
                break;
            //itemHorizontal.x
            *(result+offset) = i1;
            //itemHorizontal.y
            offset += sizeof(int);
            *(result+offset) = line;
            //itemHorizontal.x
            offset += sizeof(int);
            *(result+offset) = i2;
            //itemHorizontal.y
            offset += sizeof(int);
            *(result+offset) = line;

            //itemVertical.x
            offset += sizeof(int);
            *(result+offset) = i1;
            //itemVertical.y
            offset += sizeof(int);
            *(result+offset) = line;
            //itemVertical.x
            offset += sizeof(int);
            *(result+offset) = i2;
            //itemVertical.y
            offset += sizeof(int);
            *(result+offset) = line;

            offset += sizeof(int);
        }

}

ConstraintUniqueness::operator QString() const
{
    return "Row and column "+QString::number(line)+" must be unique.";
}
