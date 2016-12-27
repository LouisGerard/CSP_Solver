#include "file.h"
#include "constraint.h"
#include "constraint_superiority.h"

#include <QString>
#include <QFile>
#include <QtGlobal>
#include <QDebug>
#include <QByteArray>
#include <vector>

File::File(QString path) :
    path(path)
{}

Grid* File::parseGrid()
{
    if (unparsedData == "") {
        unparsedData = this->read();
        if (unparsedData == "")
            return NULL;
    }

    unsigned gridSize = unparsedData.at(0).digitValue();
    Grid* result = new Grid(gridSize);
    QString figures = "0123456789";
    unsigned cpt = 0;

    for (unsigned i = 2; i < unparsedData.length(); ++i)
        for (unsigned j = 0; j < figures.length(); ++j)
            if (unparsedData.at(i) == figures.at(j)) {
                result->assign(cpt%gridSize, cpt/gridSize, unparsedData.at(i).digitValue());
                ++cpt;
            }

    qDebug() << *result;

    return result;
}

std::vector<Constraint*> File::parseConstraints()
{
    std::vector<Constraint*> result;
    if (unparsedData == "") {
        unparsedData = this->read();
        if (unparsedData == "")
            return result;
    }

    unsigned gridSize = unparsedData.at(0).digitValue();
    unsigned cptY = 0;
    unsigned cptX = 0;

    for (unsigned i = 2; i < unparsedData.length(); ++i) {
        std::pair<unsigned, unsigned> itemSup;
        std::pair<unsigned, unsigned> itemInf;
        itemSup.second = cptY/gridSize;
        itemInf.second = cptY/gridSize;
        itemSup.first = cptX;
        itemInf.first = cptX;
        switch (unparsedData.at(i).toLatin1()) {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            ++cptY;
            ++cptX;
            break;

        case '.':
            ++cptX;
            break;

        case '\n':
            cptX = 0;
            break;

        case '<':
            --itemInf.first;
            result.push_back(new ConstraintSuperiority(itemSup, itemInf));
            break;

        case '>':
            --itemSup.first;
            result.push_back(new ConstraintSuperiority(itemSup, itemInf));
            break;

        case 'v':
            --itemSup.second;
            result.push_back(new ConstraintSuperiority(itemSup, itemInf));
            break;

        case '^':
            --itemInf.second;
            result.push_back(new ConstraintSuperiority(itemSup, itemInf));
            break;

        }
    }

    for (unsigned i = 0; i < result.size(); ++i)
        qDebug() << *result[i];

    return result;
}

QString File::read()
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Ouverture du fichier impossible !");
        return "";
    }

    QString result;
    while(!file.atEnd())
        result += file.readLine();

    file.close();
    qDebug().noquote() << "Fichier lu :\n" + result;
    return result;
}
