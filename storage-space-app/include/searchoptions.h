#ifndef SEARCHOPTIONS_H
#define SEARCHOPTIONS_H

#include <QDir>

class SearchOptions {
public:
    SearchOptions();

    QDir directory;
    bool isRecursive = false;
    int minFileSizeBytes = -1;
    int maxFileSizeBytes = -1;
};

#endif // SEARCHOPTIONS_H
