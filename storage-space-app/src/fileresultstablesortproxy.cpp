#include "fileresult.h"
#include "fileresultstable.h"
#include "fileresultstablesortproxy.h"

FileResultsTableSortProxy::FileResultsTableSortProxy()
{
    auto *worker = new FileResultsTableSortProxyWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(
        this,
        &FileResultsTableSortProxy::startSort,
        worker,
        &FileResultsTableSortProxyWorker::sort);
    connect(worker, SIGNAL(sortingComplete()), this, SLOT(onSortingComplete()));
    workerThread.start();
}

bool FileResultsTableSortProxy::lessThan(
    const QModelIndex &source_left,
    const QModelIndex &source_right) const
{
    int column = source_left.column();
    auto left = sourceModel()->data(source_left, Qt::UserRole);
    auto right = sourceModel()->data(source_right, Qt::UserRole);
    switch (column)
    {
        case FileResultsTable::PATH_COL:
        {
            auto leftPath = left.toString();
            auto rightPath = right.toString();
            return leftPath < rightPath;
        }
        case FileResultsTable::SIZE_COL:
        {
            auto leftSize = left.toLongLong();
            auto rightSize = right.toLongLong();
            return leftSize < rightSize;
        }
        default:
        {
            return false;
        }
    }
}

QModelIndex FileResultsTableSortProxy::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

void FileResultsTableSortProxy::sort(int column, Qt::SortOrder order)
{
    emit sortingInProgress(true);
    if (!sorting)
    {
        sorting = true;
        emit startSort(this, column, order);
    }
}

void FileResultsTableSortProxy::superSort(int column, Qt::SortOrder order)
{
    QSortFilterProxyModel::sort(column, order);
}

void FileResultsTableSortProxy::onSortingComplete()
{
    emit sortingInProgress(false);
    sorting = false;
}
