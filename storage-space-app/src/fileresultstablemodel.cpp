#include "fileresultstablemodel.h"

FileResultsTableModel::FileResultsTableModel(QVector<FileResult> *results)
{
    this->results = results;
}

FileResultsTableModel::~FileResultsTableModel()
{
}

int FileResultsTableModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return results->count();
}

int FileResultsTableModel::columnCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return headers.count();
}

QVariant FileResultsTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        FileResult result = results->at(index.row());
        switch (index.column())
        {
            case 0:
            {
                return result.path;
                break;
            }
            case 1:
            {
                double bytes = static_cast<double>(result.fileSizeInBytes);
                QString size;
                QString unit;
                if (bytes < 1e6)
                {
                    size = QString::number(bytes / 1e3, 'c', 3);
                    unit = "KB";
                }
                else if (bytes < 1e9)
                {
                    size = QString::number(bytes / 1e6, 'c', 3);
                    unit = "MB";
                }
                else if (bytes < 1e12)
                {
                    size = QString::number(bytes / 1e9, 'c', 3);
                    unit = "GB";
                }
                else
                {
                    size = QString::number(bytes / 1e12, 'c', 3);
                    unit = "TB";
                }
                return QString("%1 %2").arg(size, unit);
                break;
            }
            default:
            {
                return QVariant();
            }
        }
    }
    else if (role == Qt::UserRole)
    {
        FileResult result = results->at(index.row());
        return QVariant::fromValue(result);
    }
    return QVariant();
}

QModelIndex FileResultsTableModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

QVariant FileResultsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
    {
        return QVariant();
    }
    return headers.at(section);
}

Qt::ItemFlags FileResultsTableModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void FileResultsTableModel::setRows(const QVector<FileResult> &results)
{
    this->results->clear();
    this->results->append(results);
    emit layoutChanged();
}

bool FileResultsTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (results->empty())
    {
        return false;
    }
    int lastRow = row + count - 1;
    beginRemoveRows(parent, row, lastRow);
    for (int i = row; i < row + count; ++i)
    {
        results->removeAt(row);
    }
    emit dataChanged(index(row, 0), index(lastRow, NUM_COLS), { Qt::DisplayRole });
    endRemoveRows();
    return true;
}

bool FileResultsTableModel::removeRow(int row, const QModelIndex &parent)
{
    return removeRows(row, 1, parent);
}

bool FileResultsTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    emit dataChanged(index(row, 0), index(row + count - 1, NUM_COLS), { Qt::DisplayRole });
    return true;
}

bool FileResultsTableModel::insertRow(int row, const QModelIndex &parent)
{
    return insertRows(row, 1, parent);
}

void FileResultsTableModel::setHeaders(const QStringList &headers)
{
    this->headers = headers;
}
