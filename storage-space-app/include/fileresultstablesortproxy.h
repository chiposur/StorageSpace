#ifndef FILERESULTSTABLESORTPROXY_H
#define FILERESULTSTABLESORTPROXY_H

#include <QSortFilterProxyModel>
#include <QThread>

#include "fileresult.h"
#include "fileresultstablesortproxyworker.h"

class FileResultsTableSortProxy : public QSortFilterProxyModel
{
    Q_OBJECT
    QThread workerThread;

public:
    FileResultsTableSortProxy();

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    QModelIndex parent(const QModelIndex &index) const;

    void superSort(int column, Qt::SortOrder order = Qt::AscendingOrder);

signals:
    void sortingInProgress(bool inProgress);
    void startSort(FileResultsTableSortProxy *sortProxy, int column, Qt::SortOrder order);

private slots:
    void onSortingComplete();

private:
    bool sorting = false;
};

#endif // FILERESULTSTABLESORTPROXY_H
