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
    //can be replaced by an array of counters
    int* domains[gridSize*gridSize];
    int* defaultDomain = (int*) malloc(gridSize);
    for (unsigned i = 1; i <= gridSize; ++i)
        defaultDomain[i] = i;
    int domainsOffsets[gridSize*gridSize];
    for (unsigned i = 0; i < gridSize*gridSize; ++i)
        domainsOffsets[i] = 0;

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
        if (stackTop == -1) {
            for (unsigned i = 0; i < gridSize*gridSize; ++i)
                delete domains[i];
            return grid;
        }
        if (stackTop == nbVars) {
            for (unsigned i = 0; i < gridSize*gridSize; ++i)
                delete domains[i];
            return nullptr;
        }

        unsigned currentItem = varStack[stackTop];

        //eval domain
        for (; domainsOffsets[stackTop] < gridSize; ++domainsOffsets[stackTop]) {
            *(grid+currentItem) = *(domains[stackTop]+domainsOffsets[stackTop]);
            if (isConsistantC(grid)) {
                --stackTop;
                goto continue_while;
            }
        }

        //reinit domain
        domains[stackTop] = (int*) malloc(gridSize);
        memcpy(domains[stackTop], defaultDomain, gridSize);

        //reinit grid
        *(grid+currentItem) = 0;

        ++stackTop;
    }
}

bool AI::isConsistantC(int* grid, constraint * constraints[])
{

}

