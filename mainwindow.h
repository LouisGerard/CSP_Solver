#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grid.h"
#include "constraint.h"
#include<vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* getInstance();
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    unsigned getGridSize();

public slots:
    void go();

private:
    static MainWindow* instance;
    void clean();
    void setGridView();
    void updateGridView();
    void updateConstraints();
    void fillGrid();
    void createConstraints();
    void createConstraintsSuperiorityHorizontal();
    void createConstraintsSuperiorityVertical();
    void createConstraintsUniqueness();

    Ui::MainWindow *ui;
    unsigned gridSize;
    Grid* grid;
    std::vector<Constraint*> constraints;
};

#endif // MAINWINDOW_H
