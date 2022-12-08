#include <QMetaType>
#include <QVBoxLayout>

#include "filesearchworker.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<SearchOptions>("SearchOptions");
    qRegisterMetaType<QVector<FileResult>>("QVector<FileResult>");
    setWindowTitle("Storage Space");
    setMinimumSize(QSize(600, 400));
    setCentralWidget(new QWidget());
    mainLayout = new QVBoxLayout();
    centralWidget()->setLayout(mainLayout);
    searchBar = new FileSearchBar(this);
    connect(searchBar, SIGNAL(searchClicked(SearchOptions)), this, SLOT(onSearchClicked(SearchOptions)));
    mainLayout->addWidget(searchBar);
    mainLayout->addStretch();
    FileSearchWorker *worker = new FileSearchWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::startSearch, worker, &FileSearchWorker::search);
    connect(worker, &FileSearchWorker::resultsReady, this, &MainWindow::searchFinished);
    workerThread.start();
}

void MainWindow::onSearchClicked(SearchOptions options)
{
    emit startSearch(options);
}


void MainWindow::searchFinished(const QVector<FileResult> &results)
{
    this->results = results;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    workerThread.exit();
    QMainWindow::closeEvent(event);
}
