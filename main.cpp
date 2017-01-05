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

void test() {
    testSuperiority();
    testUniqueness();
}

int main(int argc, char *argv[])
{
    test();
    QApplication a(argc, argv);
    MainWindow w;

    return a.exec();
}
