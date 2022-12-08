#ifndef FILESEARCHWORKER_H
#define FILESEARCHWORKER_H

#include <QObject>

#include "fileresult.h"
#include "searchoptions.h"

class FileSearchWorker : public QObject
{
    Q_OBJECT

public:
    void search(SearchOptions options);

signals:
    void resultsReady(const QVector<FileResult> &results);
};

#endif // FILESEARCHWORKER_H
