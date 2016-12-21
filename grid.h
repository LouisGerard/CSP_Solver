#ifndef GRID_H
#define GRID_H


class Grid
{
public:
    Grid(unsigned size);
    unsigned get(unsigned x, unsigned y);
    bool assign(unsigned x, unsigned y, unsigned value);
    unsigned length();
private:
    unsigned *grid[];
};

#endif // GRID_H
