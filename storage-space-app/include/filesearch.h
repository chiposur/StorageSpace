#ifndef FILESEARCH_H
#define FILESEARCH_H

#include <QObject>

#include "searchoptions.h"

class FileSearch : QObject
{
    Q_OBJECT

public:
    FileSearch(SearchOptions options, QObject *parent = nullptr);
    ~FileSearch();

private:
    SearchOptions options;
};

#endif // FILESEARCH_H
