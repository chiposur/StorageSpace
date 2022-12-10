#ifndef FILERESULTSTABLESORTPROXY_H
#define FILERESULTSTABLESORTPROXY_H

#include <QSortFilterProxyModel>

#include "fileresult.h"

class FileResultsTableSortProxy : public QSortFilterProxyModel
{
public:
    FileResultsTableSortProxy();

    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

    void setItems(const QVector<FileResult> &results);

private:
    QVector<FileResult> results;
};

#endif // FILERESULTSTABLESORTPROXY_H
