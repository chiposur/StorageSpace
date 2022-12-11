#ifndef FILERESULTSTABLE_H
#define FILERESULTSTABLE_H

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

private slots:
    void onSortingInProgress(bool inProgress);

private:
    FileResultsTableModel *model;
    FileResultsTableSortProxy *sortProxy;
};

#endif // FILERESULTSTABLE_H
