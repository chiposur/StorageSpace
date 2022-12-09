#ifndef FILERESULTSTABLE_H
#define FILERESULTSTABLE_H

#include <QTableView>

#include "fileresult.h"
#include "fileresultstablemodel.h"

class FileResultsTable : public QTableView
{
    Q_OBJECT

public:
    FileResultsTable(QWidget *parent = nullptr);
    ~FileResultsTable();

    void setItems(const QVector<FileResult> &results);

private:
    FileResultsTableModel *model;
};

#endif // FILERESULTSTABLE_H
