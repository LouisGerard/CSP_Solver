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
    int sizeOfGrid = sizeof(int)*base->size()*base->size();
    int* grid = (int*) malloc(sizeOfGrid);
    memcpy(grid, base->toC(),sizeOfGrid);

}

bool AI::isConsistantC(int* grid)
{

}

