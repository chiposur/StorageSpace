#ifndef FILERESULT_H
#define FILERESULT_H

#include <QMetaType>
#include <QString>

class FileResult {
public:
    FileResult();
    FileResult(const FileResult &other);

    FileResult &operator=(const FileResult &other);
    bool operator==(const FileResult &other);

    QString getFormattedFileSize() const;

    QString path;
    qint64 fileSizeInBytes;
};

Q_DECLARE_METATYPE(FileResult);

#endif // FILERESULT_H
