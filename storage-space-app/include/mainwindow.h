#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>

#include "fileresult.h"
#include "filesearchbar.h"
#include "fileresultstable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread workerThread;

public:
    MainWindow(QWidget *parent = nullptr);

signals:
    void startSearch(SearchOptions options);

private slots:
    void onSearchClicked(SearchOptions options);
    void searchFinished(const QVector<FileResult> &results);
    void closeEvent(QCloseEvent *event);
    void deleteFile(QFile &file, QDir dir);
    void openInFolder(QFileInfo file);
    void onResultsTimerTick();

private:
    QString resultsTimeString();

    QVector<FileResult> results;
    QMap<QString, int> dirToResultsIndex;
    QVBoxLayout *mainLayout;
    FileSearchBar *searchBar;
    QLabel *resultsCountLabel;
    QLabel *resultsTimeLabel;
    FileResultsTable *resultsTable;
    QTimer *resultsTimer;
    static const int RESULTS_TIMER_INTERVAL_MS = 30;
    int resultsTimeMs = 0;
};
#endif // MAINWINDOW_H
