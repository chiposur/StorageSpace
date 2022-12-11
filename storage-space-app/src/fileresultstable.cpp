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
    sortProxy = new FileResultsTableSortProxy();
    sortProxy->setSourceModel(model);
    setModel(sortProxy);
    setItemDelegate(new FileResultsTableDelegate());
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    setMouseTracking(true);
    setSortingEnabled(true);
    connect(sortProxy, SIGNAL(sortingInProgress(bool)), this, SLOT(onSortingInProgress(bool)));
}

FileResultsTable::~FileResultsTable()
{
}

void FileResultsTable::onSortingInProgress(bool inProgress)
{
    setDisabled(inProgress);
    horizontalHeader()->setDisabled(inProgress);
    if (inProgress)
    {
        sortStarted();
    }
    else
    {
        sortFinished();
    }
}

void FileResultsTable::setItems(const QVector<FileResult> &results)
{
    sortProxy->setItems(results);
    model->setRows(results);
}
