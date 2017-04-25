#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <utility>

class Heuristic
{
public:
    virtual std::pair<unsigned, unsigned> next() = 0;
    virtual bool end() = 0;
    virtual void reset() = 0;
};

#endif // HEURISTIC_H
