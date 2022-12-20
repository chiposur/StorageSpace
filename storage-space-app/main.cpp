#include "filesearch.h"
#include "mainwindow.h"
#include "searchoptions.h"

#include <algorithm>
#include <iostream>
#include <QApplication>
#include <QCommandLineParser>

struct {
    bool operator()(FileResult a, FileResult b) const {
        return a.path < b.path;
    }
} pathLess;

struct {
    bool operator()(FileResult a, FileResult b) const {
        return a.path > b.path;
    }
} pathGreater;

struct {
    bool operator()(FileResult a, FileResult b) const {
        return a.fileSizeInBytes < b.fileSizeInBytes;
    }
} sizeLess;

struct {
    bool operator()(FileResult a, FileResult b) const {
        return a.fileSizeInBytes > b.fileSizeInBytes;
    }
} sizeGreater;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc <= 1)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    QCommandLineParser parser;
    parser.setApplicationDescription("Storage Space");
    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption dirOption(
        { "d", "dir" },
        "Directory to search from.",
        "search directory"
    );
    const QCommandLineOption searchTxtOption(
        "search-text",
        "Contains search text for filename.",
        "search text"
    );
    const QCommandLineOption searchRegexOption(
        "search-regex",
        "Regular expression for filename.",
        "search regex"
    );
    const QCommandLineOption recursiveOption(
        "r",
        "Recursive file search."
    );
    const QCommandLineOption minOption(
        "min",
        "Minimum file size in bytes.",
        "minimum file size"
    );
    const QCommandLineOption maxOption(
        "max",
        "Maximum file size in bytes.",
        "maximum file size"
    );
    const QCommandLineOption sortByOption(
        "sort-by",
        "Field to sort by (\"path\", \"size\".",
        "sort field"
    );
    const QCommandLineOption ascOption(
        "asc",
        "If sort-by is specified, sort ascending (default)."
    );
    const QCommandLineOption descOption(
        "desc",
        "If sort-by is specified, sort descending."
    );
    parser.addOptions({
       dirOption,
       searchTxtOption,
       searchRegexOption,
       recursiveOption,
       minOption,
       maxOption,
       sortByOption,
       ascOption,
       descOption
    });
    parser.process(QCoreApplication::arguments());
    if (parser.isSet(helpOption))
    {
        parser.showHelp();
        return 0;
    }
    SearchOptions options;
    if (parser.isSet(dirOption))
    {
        options.directory = QDir(parser.value(dirOption));
    }
    else
    {
        parser.showHelp();
        return 0;
    }
    if (parser.isSet(searchTxtOption))
    {
        options.fileNameContainsTxt = parser.value(searchTxtOption);
    }
    if (parser.isSet(searchRegexOption))
    {
        options.fileNameExpr = parser.value(searchRegexOption);
    }
    if (parser.isSet(recursiveOption))
    {
        options.isRecursive = true;
    }
    if (parser.isSet(minOption))
    {
        bool ok;
        qint64 minBytes = parser.value(minOption).toLongLong(&ok);
        if (ok && minBytes >= 0)
        {
            options.minFileSizeBytes = minBytes;
        }
        else
        {
            std::cout << "Min file size must be a valid 64 bit integer >= 0.\n";
            return 0;
        }
    }
    if (parser.isSet(maxOption))
    {
        bool ok;
        qint64 maxBytes = parser.value(maxOption).toLongLong(&ok);
        if (ok && maxBytes >= 0)
        {
            options.maxFileSizeBytes = maxBytes;
        }
        else
        {
            std::cout << "Max file size must be a valid 64 bit integer >= 0.\n";
            return 0;
        }
    }
    bool asc = true;
    QString sortField;
    if (parser.isSet(sortByOption))
    {
        sortField = parser.value(sortByOption).toLower();
        if (sortField != "path" && sortField != "size")
        {
            std::cout << "Sort field must be path or size\n";
            return 0;
        }
        if (parser.isSet(ascOption))
        {
            asc = true;
        }
        if (parser.isSet(descOption))
        {
            asc = false;
        }
    }
    FileSearch fs(options);
    QVector<FileResult> results = fs.run();
    if (sortField == "path")
    {
        if (asc)
        {
            std::sort(results.begin(), results.end(), pathLess);
        }
        else
        {
            std::sort(results.begin(), results.end(), pathGreater);
        }
    }
    else if (sortField == "size")
    {
        if (asc)
        {
            std::sort(results.begin(), results.end(), sizeLess);
        }
        else
        {
            std::sort(results.begin(), results.end(), sizeGreater);
        }
    }
    for (int i = 0; i < results.count(); ++i)
    {
        const FileResult result = results.at(i);
        QString formattedResult =
            QString("%1 - %2\n").arg(result.path, result.getFormattedFileSize());
        std::cout << formattedResult.toStdString();
    }
    return 0;
}
