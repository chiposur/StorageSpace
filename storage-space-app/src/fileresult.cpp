#include "fileresult.h"

FileResult::FileResult()
{
}

FileResult::FileResult(const FileResult& other)
{
    path = other.path;
    fileSizeInBytes = other.fileSizeInBytes;
}

FileResult &FileResult::operator=(const FileResult &other)
{
    path = other.path;
    fileSizeInBytes = other.fileSizeInBytes;
    return *this;
}

bool FileResult::operator==(const FileResult &other)
{
    return path == other.path &&
        fileSizeInBytes == other.fileSizeInBytes;
}

QString FileResult::getFormattedFileSize() const
{
    double bytes = static_cast<double>(fileSizeInBytes);
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
}
