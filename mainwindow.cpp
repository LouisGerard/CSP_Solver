#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include <QInputDialog>
#include <QDebug>
#include <QSpinBox>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    unsigned gridSize = QInputDialog::getInt(this, "Taille de la grille", "Entrez une taille : ", 5, 4, 10);
    grid = new Grid(gridSize);

    ui->setupUi(this);
    setGridView();
    this->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGridView()
{
    QStringList opList;
    opList << " " << "<" << ">";

    unsigned gridSize = grid->size();

    for (unsigned y = 0; y < gridSize; ++y) {
        unsigned x = 0;
        while (true) {
            QSpinBox* caseWidget = new QSpinBox();
            caseWidget->setMaximum(gridSize);
            caseWidget->setMinimum(0);
            ui->gridLayout->addWidget(caseWidget, 2*y, x*2);

            if(x++ == gridSize-1)
                break;

            QComboBox* operatorWidget = new QComboBox();
            operatorWidget->insertItems(1, opList);
            ui->gridLayout->addWidget(operatorWidget, 2*y, (x-1)*2+1);
        }

        for (unsigned xBox = 0; xBox < gridSize; ++xBox) {
            QComboBox* operatorWidget = new QComboBox();
            operatorWidget->insertItems(1, opList);
            ui->gridLayout->addWidget(operatorWidget, 2*y+1, xBox*2);
        }
    }
}
