#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include <QInputDialog>
#include <QDebug>
#include <QSpinBox>
#include <QComboBox>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    unsigned gridSize = QInputDialog::getInt(this, "Taille de la grille", "Entrez une taille : ", 5, 4, 10);
    grid = new Grid(gridSize);

    ui->setupUi(this);
    setGridView();

    QObject::connect(ui->goButton, SIGNAL(clicked()), this, SLOT(go()));
    this->show();
    instance = this;
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow* MainWindow::getInstance()
{
    return instance;
}

void MainWindow::go()
{
    setEnabled(false);
    fillGrid();
    createConstraints();
    setEnabled(true);
}

void MainWindow::setGridView()
{
    QStringList opList;
    opList << " " << "<" << ">";

    unsigned gridSize = grid->size();

    unsigned y = 0;
    while(true) {
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

        if (y++ == gridSize-1)
            break;

        for (unsigned xBox = 0; xBox < gridSize; ++xBox) {
            QComboBox* operatorWidget = new QComboBox();
            operatorWidget->insertItems(1, opList);
            ui->gridLayout->addWidget(operatorWidget, 2*(y-1)+1, xBox*2);
        }
    }
}

void MainWindow::fillGrid()
{
    unsigned gridSize = grid->size();
    for (unsigned x = 0; x < gridSize; ++x) {
        for (unsigned y = 0; y < gridSize; ++y) {
            QSpinBox* input = (QSpinBox*) ui->gridLayout->itemAtPosition(y*2, x*2)->widget();
            unsigned value = input->value();
            grid->assign(x, y, value);
        }
    }
    qDebug().noquote() << "Grid filled :\n" + *grid;
}

void MainWindow::createConstraints()
{

}
