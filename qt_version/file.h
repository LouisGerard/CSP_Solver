#ifndef FILE_H
#define FILE_H

#include <QString>
#include <vector>
#include "constraint.h"
#include "grid.h"

class File
{
public:
    File(QString path);
    Grid* parseGrid();
    std::vector<Constraint*> parseConstraints();

private:
    QString read();

    QString path;
    QString unparsedData = "";
};

#endif // FILE_H
