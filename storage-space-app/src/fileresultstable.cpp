#include <QHeaderView>

#include "fileresultstable.h"
#include "fileresultstabledelegate.h"

FileResultsTable::FileResultsTable(QWidget *parent)
    : QTableView(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    model = new FileResultsTableModel();
    QStringList headers;
    headers << "File Path" << "Size" << "" << "";
    model->setHeaders(headers);
    setModel(model);
    setItemDelegate(new FileResultsTableDelegate());
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    setMouseTracking(true);
}

FileResultsTable::~FileResultsTable()
{
}

void FileResultsTable::setItems(const QVector<FileResult> &results)
{
    model->setRows(results);
}
