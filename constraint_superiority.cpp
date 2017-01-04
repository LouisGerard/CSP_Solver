#include "constraint_superiority.h"
#include "grid.h"
#include <utility>

ConstraintSuperiority::ConstraintSuperiority(std::pair<unsigned, unsigned> item1, std::pair<unsigned, unsigned> item2) :
    itemSup(item1), itemInf(item2)
{}

bool ConstraintSuperiority::eval(Grid& grid)
{
    return grid.get(itemSup.first, itemSup.second) > grid.get(itemInf.first, itemInf.second);
}

int *ConstraintSuperiority::toC()
{
    int* result = (int*) malloc(sizeof(int)*6);
    //size
    *result = 1;
    //operation
    *(result+1) = 1;
    //items
    *(result+2) = itemSup.first;
    *(result+3) = itemSup.second;
    *(result+4) = itemInf.first;
    *(result+5) = itemInf.second;
    return result;
}

std::pair<unsigned, unsigned> ConstraintSuperiority::getItemSup() const
{
    return itemSup;
}

void ConstraintSuperiority::setItemSup(const std::pair<unsigned, unsigned> &value)
{
    itemSup = value;
}

std::pair<unsigned, unsigned> ConstraintSuperiority::getItemInf() const
{
    return itemInf;
}

void ConstraintSuperiority::setItemInf(const std::pair<unsigned, unsigned> &value)
{
    itemInf = value;
}

ConstraintSuperiority::operator QString() const
{
    return "(" + QString::number(itemSup.first) +
            ", " + QString::number(itemSup.second) + ")" +
            " > " +
            "(" + QString::number(itemInf.first) +
            ", " + QString::number(itemInf.second) + ")";
}
