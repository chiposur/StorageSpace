#include "fileresultstablemodel.h"

FileResultsTableModel::FileResultsTableModel()
{
}

FileResultsTableModel::~FileResultsTableModel()
{
}

int FileResultsTableModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return results.count();
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
        FileResult result = results.at(index.row());
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
    this->results = results;
    emit layoutChanged();
    emit dataChanged(index(0, 0), index(results.count() - 1, 3));
}

void FileResultsTableModel::setHeaders(const QStringList &headers)
{
    this->headers = headers;
}
