#include "fileresultstablesortproxy.h"
#include "fileresultstablesortproxyworker.h"

void FileResultsTableSortProxyWorker::sort(FileResultsTableSortProxy *sortProxy, int column, Qt::SortOrder order)
{
    sortProxy->superSort(column, order);
    emit sortingComplete();
}
