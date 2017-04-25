#ifndef ITEM_H
#define ITEM_H

#include <vector>

class Item
{
public:
    Item();
    operator =(unsigned value);
    operator unsigned() const;

    std::vector<unsigned> getDomain() const;
    void setDomain(unsigned gridSize);
    void removeDomain(unsigned value);

private:
    unsigned value = 0;
    std::vector<unsigned> domain;
};

#endif // ITEM_H
