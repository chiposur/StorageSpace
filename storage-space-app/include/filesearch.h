#ifndef FILESEARCH_H
#define FILESEARCH_H

#include <QVector>
#include <QObject>

#include "fileresult.h"
#include "searchoptions.h"

class FileSearch : QObject
{
    Q_OBJECT

public:
    FileSearch(SearchOptions options, QObject *parent = nullptr);
    QVector<FileResult> run();

private:
    void searchFiles(QDir dir);
    bool isMatch(QFileInfo fileInfo);

    SearchOptions options;
    QVector<FileResult> results;
};

#endif // FILESEARCH_H
