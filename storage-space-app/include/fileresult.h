#ifndef FILERESULT_H
#define FILERESULT_H

#include <QString>

class FileResult {
public:
    FileResult();

    QString path;
    qint64 fileSizeInBytes;
};

#endif // FILERESULT_H
