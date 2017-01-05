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

    int varStack[gridSize*gridSize];
    int stackTop = -1;
    for (int* item = grid; item-grid < gridSize; ++i)
        if (*item != 0)
            varStack[++stackTop] = item-grid;

    unsigned nbVars = stackTop + 1;

    while (stackTop != -1) {
        unsigned currentItem = varStack[stackTop];
        //domain
        for (unsigned i = 0; i < gridSize; ++i) {
            *(grid+currentItem) = i;
            if (isConsistantC(grid))
                ;//--stackTop & break while
        }
        //++stackTop
    }

    delete grid;
}

bool AI::isConsistantC(int* grid)
{

}

