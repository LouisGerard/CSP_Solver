#include "item.h"

#include <vector>

Item::Item()
{}

Item::operator =(unsigned value)
{
    this->value = value;
    return value;
}

std::vector<unsigned> Item::getDomain() const
{
    return domain;
}

void Item::setDomain(unsigned gridSize)
{
    for (unsigned i = 1; i <= gridSize; ++i)
        domain.push_back(i);
}

void Item::removeDomain(unsigned value)
{
    for (std::vector<unsigned>::iterator i = domain.begin(); i < domain.end(); ++i)
        if (*i == value)
            domain.erase(i);
}

Item::operator unsigned() const
{
    return value;
}
