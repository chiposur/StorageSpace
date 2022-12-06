#ifndef SEARCHOPTIONS_H
#define SEARCHOPTIONS_H

#include <QDir>

class SearchOptions {
public:
    SearchOptions();

    QDir directory;
    bool isRecursive = true;
    int minFileSizeBytes = -1;
    int maxFileSizeBytes = -1;
    QString fileNameExpr = "";
};

#endif // SEARCHOPTIONS_H
