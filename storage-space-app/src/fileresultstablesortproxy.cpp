#include "fileresult.h"
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
    FileResult leftResult = sourceModel()->data(source_left, Qt::UserRole).value<FileResult>();
    FileResult rightResult = sourceModel()->data(source_right, Qt::UserRole).value<FileResult>();
    switch (column)
    {
        case 0:
        {
            return leftResult.path < rightResult.path;
        }
        case 1:
        {
            return leftResult.fileSizeInBytes < rightResult.fileSizeInBytes;
        }
        default:
        {
            return false;
        }
    }
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
