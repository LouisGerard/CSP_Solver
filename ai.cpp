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

    //constraints
    constraint* constraintsC[constraints.size()];
    for (unsigned i = 0; i < constraints.size(); ++i)
        constraintsC[i] = constraints[i]->toC();

    //vars
    int varStack[gridSize*gridSize];
    int stackTop = -1;

    //domains
    //can be replaced by an array of counters
    int* domains[gridSize*gridSize];
    int* defaultDomain = (int*) malloc(gridSize);
    for (int i = 1; i <= gridSize; ++i)
        *(defaultDomain+i-1) = i;
    int domainsOffsets[gridSize*gridSize];
    for (unsigned i = 0; i < gridSize*gridSize; ++i)
        domainsOffsets[i] = 0;

    //assign
    for (int* item = grid; item-grid < gridSize*gridSize; ++item) {
        if (*item == 0) {
            varStack[++stackTop] = item-grid;
            domains[stackTop] = (int*) malloc(gridSize*sizeof(int));
            memcpy(domains[stackTop], defaultDomain, gridSize*sizeof(int));
        }
    }

    unsigned nbVars = stackTop + 1;

    while (true) {
        continue_while:
        if (stackTop == -1) {
            for (unsigned i = 0; i < nbVars; ++i)
                delete domains[i];
            return grid;
        }
        if (stackTop == nbVars) {
            for (unsigned i = 0; i < nbVars; ++i)
                delete domains[i];
            return nullptr;
        }

        unsigned currentItem = varStack[stackTop];

        //eval domain
        for (; domainsOffsets[stackTop] < gridSize; ++domainsOffsets[stackTop]) {
            *(grid+currentItem) = *(domains[stackTop]+domainsOffsets[stackTop]);
            if (isConsistantC(grid, constraintsC, constraints.size(), gridSize)) {
                --stackTop;
                goto continue_while;
            }
        }

        //reinit domain
        domainsOffsets[stackTop] = 0;

        //reinit grid
        *(grid+currentItem) = 0;

        ++stackTop;
        ++domainsOffsets[stackTop];
    }
}

int *AI::ForwardCheckingC()
{

}

bool AI::isConsistantC(int* grid, constraint* constraints[], unsigned consSize, unsigned gridSize)
{
    for (unsigned c = 0; c < consSize; ++c) {
        for (unsigned a = 0; a < constraints[c]->size; ++a) {
            unsigned x1 = *(constraints[c]->array+a*4);
            unsigned y1 = *(constraints[c]->array+a*4+1);
            unsigned x2 = *(constraints[c]->array+a*4+2);
            unsigned y2 = *(constraints[c]->array+a*4+3);
            int item1 = *(grid+y1*gridSize+x1);
            int item2 = *(grid+y2*gridSize+x2);
            if (!constraints[c]->operation(item1, item2))
                return false;
        }
    }
    return true;
}

bool AI::filterDomainsC(int item,
                        int *grid,
                        constraint *constraints[],
                        unsigned consSize,
                        unsigned gridSize,
                        int & domains[][],
                        int & domSizes[])
{
    for (unsigned c = 0; c < consSize; ++c) {
        for (unsigned a = 0; a < constraints[c]->size; ++a) {
            unsigned x1 = *(constraints[c]->array+a*4);
            unsigned y1 = *(constraints[c]->array+a*4+1);
            unsigned x2 = *(constraints[c]->array+a*4+2);
            unsigned y2 = *(constraints[c]->array+a*4+3);
            int item1 = grid+y1*gridSize+x1;
            int item2 = grid+y2*gridSize+x2;
            int linkedItem;
            if (item != item1) {
                if (item != item2)
                    continue;
                else
                    linkedItem = item1;
            }
            else
                linkedItem = item2;

            for (unsigned d = 0; d < gridSize; ++d) {
                if (!constraints[c]->operation(*(grid+item), domains[linkedItem][d])) {
                    //remove value from domain
                    int temp = domains[linkedItem][d];
                    domains[linkedItem][d] = domains[linkedItem][domSize-1];
                    domains[linkedItem][domSize-1] = temp;
                    --domSizes[linkedItem];
                }
            }
            //todo check if domain is empty
            if (domSizes[linkedItem] == 0)
                return false;
        }
    }
    return true;

}

