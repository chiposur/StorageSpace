#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QVBoxLayout>

#include "fileresult.h"
#include "filesearchbar.h"

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

private:
    QVector<FileResult> results;
    QVBoxLayout *mainLayout;
    FileSearchBar *searchBar;
};
#endif // MAINWINDOW_H
