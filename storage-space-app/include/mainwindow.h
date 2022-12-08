#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "filesearchbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onSearchClicked(SearchOptions options);

private:
    QVBoxLayout *mainLayout;
    FileSearchBar *searchBar;
};
#endif // MAINWINDOW_H
