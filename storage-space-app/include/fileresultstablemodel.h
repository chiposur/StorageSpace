#ifndef FILERESULTSTABLEMODEL_H
#define FILERESULTSTABLEMODEL_H

#include <QAbstractTableModel>

#include "fileresult.h"

class FileResultsTableModel : public QAbstractTableModel
{
public:
    FileResultsTableModel(QVector<FileResult> *results);
    ~FileResultsTableModel();

    int rowCount(const QModelIndex &index) const;
    int columnCount(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QModelIndex parent(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());

    void setRows(const QVector<FileResult> &results);
    void setHeaders(const QStringList &headers);

private:
    QVector<FileResult> *results;
    QStringList headers;
    const static int NUM_COLS = 3;
};

#endif // FILERESULTSTABLEMODEL_H
