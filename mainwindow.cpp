#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    unsigned gridSize = QInputDialog::getInt(this, "Taille de la grille", "Entrez une taille : ", 5, 4, 10);
    grid = new Grid(gridSize);

    ui->setupUi(this);
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
