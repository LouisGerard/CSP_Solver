#include "file.h"
#include <QString>
#include <QFile>
#include <QtGlobal>
#include <QDebug>
#include <QByteArray>

File::File(QString path) :
    path(path)
{}

Grid File::parseGrid()
{
    if (unparsedData == "") {
        unparsedData = this->read();
        if (unparsedData == "")
            return NULL;
    }

    unsigned gridSize = unparsedData.at(0).digitValue();
    Grid result(gridSize);
    QString figures = "0123456789";
    unsigned cpt = 0;

    for (unsigned i = 2; i < unparsedData.length(); ++i)
        for (unsigned j = 0; j < figures.length(); ++j)
            if (unparsedData.at(i) == figures.at(j)) {
                result.assign(cpt%gridSize, cpt/gridSize, unparsedData.at(i).digitValue());
                ++cpt;
            }

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
