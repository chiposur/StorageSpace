#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QThread>
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

private:
    QVector<FileResult> results;
    QVBoxLayout *mainLayout;
    FileSearchBar *searchBar;
    QLabel *resultsCountLabel;
    FileResultsTable *resultsTable;
};
#endif // MAINWINDOW_H
