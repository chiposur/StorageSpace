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
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onCellClicked(QModelIndex)));
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
        emit sortStarted();
    }
    else
    {
        emit sortFinished();
    }
}

void FileResultsTable::setItems(const QVector<FileResult> &results)
{
    this->results = results;
    sortProxy->setItems(results);
    model->setRows(results);
}

void FileResultsTable::onCellClicked(const QModelIndex &index)
{
    auto pathIndex = sortProxy->index(index.row(), 0);
    QString path = sortProxy->data(pathIndex).toString();
    int column = index.column();
    switch (column)
    {
        case 2:
        {
            QFileInfo fileInfo = QFileInfo(path);
            emit openInFolder(fileInfo);
            break;
        }
        case 3:
        {
            QFile file = QFile(path);
            emit deleteFile(file, QDir(path));
            break;
        }
        default:
        {
            break;
        }
    }
}
