#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grid.h"
#include "constraint_superiority.h"
#include "constraint_uniqueness.h"
#include "file.h"
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
    ui->setupUi(this);

    while (true) {
        QString filePath = QInputDialog::getText(this,
                                                 "Ouverture par fichier",
                                                 "Chemin vers le fichier (facultatif) :");

        if (filePath != "") {
            File file(filePath);
            grid = file.parseGrid();
            if (grid == NULL)
                continue;
            gridSize = grid->size();
            constraints = file.parseConstraints();

            setGridView();
            updateGridView();
        }
        else {
            gridSize = QInputDialog::getInt(this, "Taille de la grille", "Entrez une taille : ", 5, 4, 10);
            setGridView();
        }
        break;
    }

    QObject::connect(ui->goButton, SIGNAL(clicked()), this, SLOT(go()));
    this->show();
    instance = this;
}

MainWindow::~MainWindow()
{
    delete grid;
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

void MainWindow::updateGridView()
{
    for (unsigned x = 0; x < gridSize; ++x) {
        for (unsigned y = 0; y < gridSize; ++y) {
            QSpinBox* caseWidget = (QSpinBox*) ui->gridLayout->itemAtPosition(y*2, x*2)->widget();
            caseWidget->setValue(grid->get(x, y));
        }
    }
    qDebug() << "View updated.";
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
    createConstraintsSuperiorityHorizontal();
    createConstraintsSuperiorityVertical();
    createConstraintsUniqueness();
    qDebug() << "Constraints created :";
    for (unsigned i = 0; i < constraints.size(); ++i)
        qDebug() << *constraints[i];
}

void MainWindow::createConstraintsSuperiorityHorizontal()
{
    for (unsigned x = 0; x < gridSize-1; ++x) {
        for (unsigned y = 0; y < gridSize; ++y) {
            std::pair<unsigned, unsigned> leftPos(x, y);
            std::pair<unsigned, unsigned> rightPos(x+1, y);

            QComboBox* input = (QComboBox*) ui->gridLayout->itemAtPosition(y*2, x*2+1)->widget();
            QString value = input->currentText();

            if (value == ">")
                constraints.push_back(new ConstraintSuperiority(leftPos, rightPos));
            else if (value == "<")
                constraints.push_back(new ConstraintSuperiority(rightPos, leftPos));
        }
    }
}

void MainWindow::createConstraintsSuperiorityVertical()
{
    for (unsigned x = 0; x < gridSize; ++x) {
        for (unsigned y = 0; y < gridSize-1; ++y) {
            std::pair<unsigned, unsigned> topPos(x, y);
            std::pair<unsigned, unsigned> bottomPos(x, y+1);

            QComboBox* input = (QComboBox*) ui->gridLayout->itemAtPosition(y*2+1, x*2)->widget();
            QString value = input->currentText();

            if (value == ">")
                constraints.push_back(new ConstraintSuperiority(topPos, bottomPos));
            else if (value == "<")
                constraints.push_back(new ConstraintSuperiority(bottomPos, topPos));
        }
    }
}

void MainWindow::createConstraintsUniqueness()
{
    for (unsigned i = 0; i < gridSize; ++i)
        constraints.push_back(new ConstraintUniqueness(i));
}
