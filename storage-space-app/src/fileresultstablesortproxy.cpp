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
    FileResult leftResult = results.at(source_left.row());
    FileResult rightResult = results.at(source_right.row());
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

void FileResultsTableSortProxy::setItems(const QVector<FileResult> &results)
{
    this->results = QVector<FileResult>(results);
}

void FileResultsTableSortProxy::onSortingComplete()
{
    emit sortingInProgress(false);
    sorting = false;
}
