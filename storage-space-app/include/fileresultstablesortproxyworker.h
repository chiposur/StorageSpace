#ifndef FILERESULTSTABLESORTPROXYWORKER_H
#define FILERESULTSTABLESORTPROXYWORKER_H

#include <QObject>

class FileResultsTableSortProxy;

class FileResultsTableSortProxyWorker : public QObject
{
    Q_OBJECT

public:
    void sort(FileResultsTableSortProxy *sortProxy, int column, Qt::SortOrder order);

signals:
    void sortingComplete();
};

#endif // FILERESULTSTABLESORTPROXYWORKER_H
