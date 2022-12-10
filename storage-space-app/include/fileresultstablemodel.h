#ifndef FILERESULTSTABLEMODEL_H
#define FILERESULTSTABLEMODEL_H

#include <QAbstractTableModel>

#include "fileresult.h"

class FileResultsTableModel : public QAbstractTableModel
{
public:
    FileResultsTableModel();
    ~FileResultsTableModel();

    int rowCount(const QModelIndex &index) const;
    int columnCount(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex parent(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

    void setRows(const QVector<FileResult> &results);
    void setHeaders(const QStringList &headers);

    QVector<FileResult> results;
    QStringList headers;
};

#endif // FILERESULTSTABLEMODEL_H
