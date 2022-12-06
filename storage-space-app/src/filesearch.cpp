#include "filesearch.h"

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
        QFileInfo fileInfo = list[0];
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
    if (options.minFileSizeBytes > -1 && fileInfo.size() < options.minFileSizeBytes)
    {
        return false;
    }
    if (options.maxFileSizeBytes > -1 && fileInfo.size() > options.maxFileSizeBytes)
    {
        return false;
    }
    return true;
}
