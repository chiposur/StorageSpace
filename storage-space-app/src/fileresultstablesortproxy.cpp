#include "fileresultstablesortproxy.h"

FileResultsTableSortProxy::FileResultsTableSortProxy()
{
}

bool FileResultsTableSortProxy::lessThan(
    const QModelIndex &source_left,
    const QModelIndex &source_right) const
{
    int column = source_left.column();
    FileResult leftResult = results.at(source_left.row());
    FileResult rightResult = results.at(source_right.row());
    switch (column) {
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

void FileResultsTableSortProxy::setItems(const QVector<FileResult> &results)
{
    this->results = QVector<FileResult>(results);
}
