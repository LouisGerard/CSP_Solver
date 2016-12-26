#include "constraint_uniqueness.h"
#include <vector>

ConstraintUniqueness::ConstraintUniqueness(unsigned line) :
    line(line)
{}

bool ConstraintUniqueness::eval(Grid* grid)
{
    std::vector<unsigned> hashHorizontal(grid->size());
    std::vector<unsigned> hashVertical(grid->size());
    for (unsigned x = 0; x < hashHorizontal.size(); ++x) {
        for (unsigned y = 0; y < hashVertical.size(); ++y) {
            unsigned valueHor = grid->get(x, line);
            if (hashHorizontal[valueHor] != 0)
                return false;
            hashHorizontal[valueHor] = 1;

            unsigned valueVer = grid->get(line, y);
            if (hashVertical[valueVer] != 0)
                return false;
            hashVertical[valueVer] = 1;
        }
    }
    return true;
}

ConstraintUniqueness::operator QString() const
{
    return "Row and column "+QString::number(line)+" must be unique.";
}
