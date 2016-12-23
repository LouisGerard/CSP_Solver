#include "constraint.h"
#include "grid.h"
#include <utility>

Constraint::Constraint(std::pair<unsigned, unsigned> item1, std::pair<unsigned, unsigned> item2) :
    itemSup(item1), itemInf(item2)
{}

bool Constraint::eval(Grid grid)
{

}

std::pair<unsigned, unsigned> Constraint::getItemSup() const
{
    return itemSup;
}

void Constraint::setItemSup(const std::pair<unsigned, unsigned> &value)
{
    itemSup = value;
}

std::pair<unsigned, unsigned> Constraint::getItemInf() const
{
    return itemInf;
}

void Constraint::setItemInf(const std::pair<unsigned, unsigned> &value)
{
    itemInf = value;
}

Constraint::operator QString() const
{
    return "(" + QString::number(itemSup.first) +
            ", " + QString::number(itemSup.second) + ")" +
            " > " +
            "(" + QString::number(itemInf.first) +
            ", " + QString::number(itemInf.second) + ")";
}
