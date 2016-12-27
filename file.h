#ifndef FILE_H
#define FILE_H

#include <QString>
#include "grid.h"

class File
{
public:
    File(QString path);
    Grid* parseGrid();

private:
    QString read();

    QString path;
    QString unparsedData = "";
};

#endif // FILE_H
