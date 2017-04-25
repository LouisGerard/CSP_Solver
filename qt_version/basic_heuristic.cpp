#include "basic_heuristic.h"

BasicHeuristic::BasicHeuristic(unsigned gridSize) :
    gridSize(gridSize)
{}

std::pair<unsigned, unsigned> BasicHeuristic::next()
{
    std::pair<unsigned, unsigned> result(x, y);
    if (x < gridSize)
        ++x;
    else {
        ++y;
        x = 0;
    }
    return result;
}

bool BasicHeuristic::end()
{
    return x==gridSize-1 && y==gridSize-1;
}

void BasicHeuristic::reset()
{
    x = 0;
    y = 0;
}
