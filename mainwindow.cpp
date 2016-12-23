#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include "constraint.h"
#include <utility>
#include <QInputDialog>
#include <QDebug>
#include <QSpinBox>
#include <QComboBox>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gridSize = QInputDialog::getInt(this, "Taille de la grille", "Entrez une taille : ", 5, 4, 10);
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
    clean();
    fillGrid();
    createConstraints();
    setEnabled(true);
}

void MainWindow::clean()
{
    delete grid;
    grid = new Grid(gridSize);
    constraints.clear();
}

void MainWindow::setGridView()
{
    QStringList opList;
    opList << " " << "<" << ">";

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
    createConstraintsHorizontal();
    createConstraintsVertical();
    qDebug() << "Constraints created :";
    for (Constraint constraint : constraints)
        qDebug() << constraint;
}

void MainWindow::createConstraintsHorizontal()
{
    for (unsigned x = 0; x < gridSize-1; ++x) {
        for (unsigned y = 0; y < gridSize; ++y) {
            std::pair<unsigned, unsigned> leftPos(x, y);
            std::pair<unsigned, unsigned> rightPos(x+1, y);

            QComboBox* input = (QComboBox*) ui->gridLayout->itemAtPosition(y*2, x*2+1)->widget();
            QString value = input->currentText();

            if (value == ">")
                constraints.push_back(Constraint(leftPos, rightPos));
            else if (value == "<")
                constraints.push_back(Constraint(rightPos, leftPos));
        }
    }
}

void MainWindow::createConstraintsVertical()
{
    for (unsigned x = 0; x < gridSize; ++x) {
        for (unsigned y = 0; y < gridSize-1; ++y) {
            std::pair<unsigned, unsigned> topPos(x, y);
            std::pair<unsigned, unsigned> bottomPos(x, y+1);

            QComboBox* input = (QComboBox*) ui->gridLayout->itemAtPosition(y*2+1, x*2)->widget();
            QString value = input->currentText();

            if (value == ">")
                constraints.push_back(Constraint(topPos, bottomPos));
            else if (value == "<")
                constraints.push_back(Constraint(bottomPos, topPos));
        }
    }
}
