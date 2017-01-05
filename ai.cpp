#include "ai.h"

#include "grid.h"
#include "constraint.h"
#include "assignment.h"
#include <utility>
#include <vector>
#include <QDebug>

AI::AI(Grid * base, std::vector<Constraint*> constraints, Heuristic *heuristic) :
    base(base),
    constraints(constraints),
    heuristic(heuristic)
{}

int* AI::BackTrackC()
{
    unsigned gridSize = base->size();
    int* grid = base->toC();

    //vars
    int varStack[gridSize*gridSize];
    int stackTop = -1;

    //domains
    int* domains[gridSize*gridSize];
    int* defaultDomain = (int*) malloc(gridSize);
    for (unsigned i = 0; i < gridSize; ++i)
        defaultDomain[i] = i;

    //assign
    for (int* item = grid; item-grid < gridSize; ++item)
        if (*item != 0) {
            varStack[++stackTop] = item-grid;
            domains[stackTop] = (int*) malloc(gridSize);
            memcpy(domains[stackTop], defaultDomain, gridSize);
        }

    unsigned nbVars = stackTop + 1;

    while (true) {
        continue_while:
        if (stackTop == -1)
            return grid;
        if (stackTop == nbVars)
            return nullptr;
        unsigned currentItem = varStack[stackTop];

        //eval domain
        for (int* i = domains[stackTop]; *i < gridSize-1; ++i) {
            *(grid+currentItem) = *i;
            if (isConsistantC(grid)) {
                --stackTop;
                goto continue_while;
            }
            else {
                delete domains[stackTop];    //juste la case ?
                ++domains[stackTop];
            }
        }

        //reinit domain
        domains[stackTop] = (int*) malloc(gridSize);
        memcpy(domains[stackTop], defaultDomain, gridSize);

        ++stackTop;
    }

    for (unsigned i = 0; i < gridSize*gridSize; ++i)
        delete domains[i];    //juste la case ?

    return grid;
}

bool AI::isConsistantC(int* grid)
{

}

