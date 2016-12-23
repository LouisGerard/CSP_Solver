#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grid.h"

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

public slots:
    void go();

private:
    static MainWindow* instance;
    void setGridView();
    void fillGrid();
    void createConstraints();

    Ui::MainWindow *ui;
    Grid* grid;
};

#endif // MAINWINDOW_H
