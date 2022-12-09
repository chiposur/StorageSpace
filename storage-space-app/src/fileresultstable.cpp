#include <QHeaderView>

#include "fileresultstable.h"

FileResultsTable::FileResultsTable(QWidget *parent)
    : QTableView(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    model = new FileResultsTableModel();
    QStringList headers;
    headers << "File Path" << "Size (MB)";
    model->setHeaders(headers);
    setModel(model);
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

FileResultsTable::~FileResultsTable()
{
}

void FileResultsTable::setItems(const QVector<FileResult> &results)
{
    model->setRows(results);
}
