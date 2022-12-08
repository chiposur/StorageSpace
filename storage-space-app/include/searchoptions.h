#ifndef SEARCHOPTIONS_H
#define SEARCHOPTIONS_H

#include <QDir>
#include <QMetaType>

class SearchOptions {
public:
    SearchOptions();

    QDir directory = QDir(".");
    bool isRecursive = true;
    qint64 minFileSizeBytes = -1;
    qint64 maxFileSizeBytes = -1;
    QString fileNameContainsTxt = "";
    QString fileNameExpr = "";
};

#endif // SEARCHOPTIONS_H
