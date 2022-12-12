#ifndef FILERESULTSTABLE_H
#define FILERESULTSTABLE_H

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTableView>

#include "fileresult.h"
#include "fileresultstablemodel.h"
#include "fileresultstablesortproxy.h"

class FileResultsTable : public QTableView
{
    Q_OBJECT

public:
    FileResultsTable(QWidget *parent = nullptr);
    ~FileResultsTable();

    void setItems(const QVector<FileResult> &results);

signals:
    void sortStarted();
    void sortFinished();
    void openInFolder(QFileInfo fileInfo);
    void deleteFile(QFile &file, QDir dir);

private slots:
    void onSortingInProgress(bool inProgress);
    void onCellClicked(const QModelIndex &);

private:
    QVector<FileResult> results;
    FileResultsTableModel *model;
    FileResultsTableSortProxy *sortProxy;
};

#endif // FILERESULTSTABLE_H
