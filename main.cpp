#include <vector>
#include <utility>
#include <QApplication>
#include <QDebug>
#include <QtGlobal>
#include "mainwindow.h"
#include "constraint.h"
#include "constraint_superiority.h"
#include "constraint_uniqueness.h"

void testSuperiority() {
    std::pair<unsigned, unsigned> itemSup(1,2);
    std::pair<unsigned, unsigned> itemInf(3,2);
    ConstraintSuperiority superiority(itemSup, itemInf);
    constraint * superiorityC = superiority.toC();

    //size
    Q_ASSERT(superiorityC->size == 1);

    //operation
    Q_ASSERT(superiorityC->operation(1, 0));
    Q_ASSERT(!superiorityC->operation(0, 1));

    //array
    int item1x = *superiorityC->array;
    Q_ASSERT(item1x == 1);
    int item1y = *(superiorityC->array+1);
    Q_ASSERT(item1y == 2);
    int item2x = *(superiorityC->array+2);
    Q_ASSERT(item2x == 3);
    int item2y = *(superiorityC->array+3);
    Q_ASSERT(item2y == 2);

    // #NeverForget
    delete superiorityC->array;
    delete superiorityC;
}

void testUniqueness() {
    ConstraintUniqueness uniqueness(1);
    //to test, assign gridSize in constraint_uniqueness.cpp
    constraint * uniquenessC = uniqueness.toC();

    //size
    Q_ASSERT(uniquenessC->size == 6);


    //operation
    Q_ASSERT(uniquenessC->operation(0, 1));
    Q_ASSERT(!uniquenessC->operation(1, 1));

    //array
    std::vector<int> expected;

    expected.push_back(0);  //item 1 x
    expected.push_back(1);  //item 1 y
    expected.push_back(1);  //item 2 x
    expected.push_back(1);  //item 2 y

    expected.push_back(1);  //item 1 x
    expected.push_back(0);  //item 1 y
    expected.push_back(1);  //item 2 x
    expected.push_back(1);  //item 2 y

    expected.push_back(0);  //item 1 x
    expected.push_back(1);  //item 1 y
    expected.push_back(2);  //item 2 x
    expected.push_back(1);  //item 2 y

    expected.push_back(1);  //item 1 x
    expected.push_back(0);  //item 1 y
    expected.push_back(1);  //item 2 x
    expected.push_back(2);  //item 2 y

    expected.push_back(1);  //item 1 x
    expected.push_back(1);  //item 1 y
    expected.push_back(2);  //item 2 x
    expected.push_back(1);  //item 2 y

    expected.push_back(1);  //item 1 x
    expected.push_back(1);  //item 1 y
    expected.push_back(1);  //item 2 x
    expected.push_back(2);  //item 2 y

    for (unsigned i = 0; i < expected.size(); ++i)
        Q_ASSERT(expected[i] == *(uniquenessC->array+i));

    delete uniquenessC->array;
    delete uniquenessC;
}

void testGrid() {
    unsigned gridSize = 3;
    Grid grid(gridSize);
    grid.assign(0, 0, 1);
    grid.assign(2, 0, 2);
    grid.assign(2, 2, 3);
    grid.assign(0, 2, 4);
    grid.assign(1, 1, 5);

    int * gridC = grid.toC();
    for (unsigned i = 0; i < gridSize*gridSize; ++i)
        Q_ASSERT(grid.get(i%gridSize, i/gridSize) == *(gridC+i));
}

void test() {
    testSuperiority();
    //testUniqueness();
    testGrid();
}

int main(int argc, char *argv[])
{
    //test();
    QApplication a(argc, argv);
    MainWindow w;

    return a.exec();
}
