#include "filesearch.h"

#include <QRegularExpression>

FileSearch::FileSearch(SearchOptions options, QObject *parent)
    : QObject(parent)
{
    this->options = options;
}

FileSearch::~FileSearch()
{
}

void FileSearch::searchFiles(QDir dir)
{
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list[i];
        if (options.isRecursive && fileInfo.isDir())
        {
            searchFiles(fileInfo.dir());
        }
        else if (fileInfo.isFile() && isMatch(fileInfo))
        {
            FileResult result;
            result.path = fileInfo.path();
            results->append(result);
        }
    }
}

bool FileSearch::isMatch(QFileInfo fileInfo)
{
    const int minFileSizeBytes = options.minFileSizeBytes;
    const int maxFileSizeBytes = options.maxFileSizeBytes;
    const QString fileNameExpr = options.fileNameExpr;
    if (minFileSizeBytes > -1 && fileInfo.size() < minFileSizeBytes)
    {
        return false;
    }
    if (maxFileSizeBytes > -1 && fileInfo.size() > maxFileSizeBytes)
    {
        return false;
    }
    if (!fileNameExpr.isEmpty() && !fileInfo.fileName().contains(QRegularExpression(fileNameExpr))) {
        return false;
    }
    return true;
}
