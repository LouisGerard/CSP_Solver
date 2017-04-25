#ifndef BASIC_HEURISTIC_H
#define BASIC_HEURISTIC_H

#include "heuristic.h"

class BasicHeuristic : public Heuristic
{
public:
    BasicHeuristic(unsigned gridSize);

    std::pair<unsigned, unsigned> next();
    bool end();
    void reset();

private:
    unsigned gridSize;
    unsigned x = 0;
    unsigned y = 0;
};

#endif // BASIC_HEURISTIC_H
