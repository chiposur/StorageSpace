#include "fileresult.h"

FileResult::FileResult()
{
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
