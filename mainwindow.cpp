#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->gridSize = QInputDialog::getInt(this, "Taille de la grille", "Entrez une taille : ", 5, 4, 10);
    qDebug() << "Grid size : " << gridSize;
    ui->setupUi(this);
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
