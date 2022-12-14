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
    void onSortStarted();
    void onSearchFinished(const QVector<FileResult> &results);
    void onSortFinished();
    void closeEvent(QCloseEvent *event);
    void onDeleteFile(QFile &file, QDir dir);
    void onOpenInFolder(QFileInfo file);
    void onResultsTimerTick();
    void onSortTimerTick();

private:
    QString resultsTimeString();
    QString resultsString();

    QVector<FileResult> results;
    QVBoxLayout *mainLayout;
    FileSearchBar *searchBar;
    QLabel *resultsCountLabel;
    QLabel *resultsTimeLabel;
    FileResultsTable *resultsTable;
    QTimer *resultsTimer;
    QTimer *sortTimer;
    QString resultsInfo = "";
    static const int RESULTS_TIMER_INTERVAL_MS = 1;
    static const int SORT_TIMER_INTERVAL_MS = 1000;
    int resultsTimeMs = 0;
    int sortTimeMs = 0;
    bool searchRun = false;
    const QIcon APP_ICON = QIcon(QPixmap(":/images/app-icon.ico"));
};
#endif // MAINWINDOW_H
