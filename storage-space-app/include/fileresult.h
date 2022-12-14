#ifndef FILERESULT_H
#define FILERESULT_H

#include <QMetaType>
#include <QString>

class FileResult {
public:
    FileResult();

    FileResult &operator=(const FileResult &fileResult);
    bool operator==(const FileResult &fileResult);

    QString path;
    qint64 fileSizeInBytes;
};

Q_DECLARE_METATYPE(FileResult);

#endif // FILERESULT_H
