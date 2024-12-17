#include "fileresultstable.h"
#include "fileresultstabledelegate.h"

#include <QHeaderView>

FileResultsTable::FileResultsTable(QVector<FileResult> *results, QWidget *parent)
    : QTableView(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    model = new FileResultsTableModel(results);
    QStringList headers;
    headers << "File Path" << "Size" << "" << "";
    model->setHeaders(headers);
    sortProxy = new FileResultsTableSortProxy();
    sortProxy->setSourceModel(model);
    setModel(sortProxy);
    setItemDelegate(new FileResultsTableDelegate());
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    horizontalHeader()->resizeSection(
        FileResultsTable::OPEN_IN_FOLDER_COL,
        120);
    horizontalHeader()->resizeSection(
        FileResultsTable::DELETE_COL,
        76);
    setMouseTracking(true);
    setSortingEnabled(false);
    connect(horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onSectionClicked(int)));
    connect(sortProxy, SIGNAL(sortingInProgress(bool)), this, SLOT(onSortingInProgress(bool)));
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onCellClicked(QModelIndex)));
}

FileResultsTable::~FileResultsTable()
{
}

void FileResultsTable::onSectionClicked(int logicalIndex)
{
    auto header = horizontalHeader();
    if (logicalIndex == OPEN_IN_FOLDER_COL || logicalIndex == DELETE_COL)
    {
        header->setSortIndicatorShown(false);
        return;
    }
    auto indicatorOrder = horizontalHeader()->sortIndicatorOrder();
    if (!indicatorOrder)
    {
        indicatorOrder = Qt::AscendingOrder;
    }
    header->setSortIndicatorShown(true);
    header->setSortIndicator(logicalIndex, indicatorOrder);
    sortProxy->sort(logicalIndex, indicatorOrder);
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

void FileResultsTable::setRows(const QVector<FileResult> &results)
{
    model->setRows(results);
}

void FileResultsTable::deleteRow(int row)
{
    model->removeRow(row);
}

void FileResultsTable::onCellClicked(const QModelIndex &index)
{
    auto pathIndex = sortProxy->index(index.row(), 0);
    QString path = sortProxy->data(pathIndex).toString();
    int column = index.column();
    switch (column)
    {
        case OPEN_IN_FOLDER_COL:
        {
            QFileInfo fileInfo = QFileInfo(path);
            emit openInFolder(fileInfo);
            break;
        }
        case DELETE_COL:
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
