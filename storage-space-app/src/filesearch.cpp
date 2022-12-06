#include "filesearch.h"

#include <QRegularExpression>

FileSearch::FileSearch(SearchOptions options, QObject *parent)
    : QObject(parent)
{
    this->options = options;
}

QVector<FileResult> FileSearch::run()
{
    searchFiles(options.directory);
    return results;
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
            results.append(result);
        }
    }
}

bool FileSearch::isMatch(QFileInfo fileInfo)
{
    const QString fileName = fileInfo.fileName();
    const int fileSize = fileInfo.size();
    const int minFileSizeBytes = options.minFileSizeBytes;
    const int maxFileSizeBytes = options.maxFileSizeBytes;
    const QString fileNameContainsTxt = options.fileNameContainsTxt;
    const QRegularExpression fileNameExpr = QRegularExpression(options.fileNameExpr);
    if (minFileSizeBytes > -1 && fileSize < minFileSizeBytes)
    {
        return false;
    }
    if (maxFileSizeBytes > -1 && fileSize > maxFileSizeBytes)
    {
        return false;
    }
    if (fileNameExpr.isValid() && !fileName.contains(fileNameExpr)) {
        return false;
    }
    return fileName.contains(fileNameContainsTxt);
}
