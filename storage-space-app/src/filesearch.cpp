#include "filesearch.h"

#include <QRegularExpression>

FileSearch::FileSearch(SearchOptions options, QObject *parent)
    : QObject(parent)
{
    this->options = options;
}

const QVector<FileResult> &FileSearch::run()
{
    QDir dir = options.directory;
    dir.refresh();
    searchFiles(dir);
    return results;
}

void FileSearch::searchFiles(QDir dir)
{
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list[i];
        bool isChildDir =
            fileInfo.isDir() &&
            fileInfo.fileName() != "." &&
            fileInfo.fileName() != "..";
        if (options.isRecursive && isChildDir)
        {
            searchFiles(fileInfo.absoluteFilePath());
        }
        else if (fileInfo.isFile() && isMatch(fileInfo))
        {
            FileResult result;
            result.path = fileInfo.absoluteFilePath();
            result.fileSizeInBytes = fileInfo.size();
            results.append(result);
        }
    }
}

bool FileSearch::isMatch(QFileInfo fileInfo)
{
    const QString fileName = fileInfo.fileName();
    const qint64 fileSize = fileInfo.size();
    const qint64 minFileSizeBytes = options.minFileSizeBytes;
    const qint64 maxFileSizeBytes = options.maxFileSizeBytes;
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
    if (fileNameExpr.isValid() && !fileName.contains(fileNameExpr))
    {
        return false;
    }
    return fileName.contains(fileNameContainsTxt);
}
