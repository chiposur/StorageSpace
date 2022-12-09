#ifndef FILERESULT_H
#define FILERESULT_H

#include <QString>

class FileResult {
public:
    FileResult();

    FileResult &operator=(const FileResult &fileResult);
    bool operator==(const FileResult &fileResult);

    QString path;
    qint64 fileSizeInBytes;
};

#endif // FILERESULT_H
