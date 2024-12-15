#ifndef SEARCHOPTIONS_H
#define SEARCHOPTIONS_H

#include <QDir>

class SearchOptions {
public:
    SearchOptions();

    QDir directory = QDir(".");
    bool isRecursive = true;
    bool isCaseSensitive = false;
    qint64 minFileSizeBytes = -1;
    qint64 maxFileSizeBytes = -1;
    qint64 maxDepth = -1;
    QString fileNameContainsTxt = "";
    QString fileNameExpr = "";
};

#endif // SEARCHOPTIONS_H
