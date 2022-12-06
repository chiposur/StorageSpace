#ifndef SEARCHOPTIONS_H
#define SEARCHOPTIONS_H

#include <QDir>

class SearchOptions {
public:
    SearchOptions();

    QDir directory;
    bool isRecursive = false;
};

#endif // SEARCHOPTIONS_H
