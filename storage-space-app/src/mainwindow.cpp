#include <QDesktopServices>
#include <QMessageBox>
#include <QMetaType>
#include <QUrl>
#include <QVBoxLayout>

#include "filesearchworker.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<SearchOptions>("SearchOptions");
    qRegisterMetaType<QVector<FileResult>>("QVector<FileResult>");
    setWindowTitle("Storage Space");
    setMinimumSize(QSize(640, 480));
    setCentralWidget(new QWidget());
    mainLayout = new QVBoxLayout();
    centralWidget()->setLayout(mainLayout);
    searchBar = new FileSearchBar(this);
    connect(searchBar, SIGNAL(searchClicked(SearchOptions)), this, SLOT(onSearchClicked(SearchOptions)));
    mainLayout->addWidget(searchBar);
    resultsCountLabel = new QLabel(this);
    resultsTable = new FileResultsTable(this);
    mainLayout->addWidget(resultsCountLabel);
    mainLayout->addWidget(resultsTable);
    FileSearchWorker *worker = new FileSearchWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::startSearch, worker, &FileSearchWorker::search);
    connect(worker, &FileSearchWorker::resultsReady, this, &MainWindow::searchFinished);
    workerThread.start();
}

void MainWindow::onSearchClicked(SearchOptions options)
{
    searchBar->setDisabled(true);
    emit startSearch(options);
}


void MainWindow::searchFinished(const QVector<FileResult> &results)
{
    searchBar->setEnabled(true);
    this->results = results;
    resultsCountLabel->setText(QString("%1 results found").arg(results.count()));
    resultsTable->setItems(results);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    workerThread.exit();
    QMainWindow::closeEvent(event);
}

void MainWindow::deleteFile(QFile &file, QDir dir)
{
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    if (file.remove())
    {
        QString absoluteFilePath = dir.absoluteFilePath(file.fileName());
        int index = dirToResultsIndex.value(absoluteFilePath, -1);
        if (index > -1)
        {
            results.removeAt(index);
            resultsTable->setItems(results);
            dirToResultsIndex.remove(absoluteFilePath);
        }
        msgBox.setText(QString("Successfully deleted \"%1\"").arg(file.fileName()));
        msgBox.setIcon(QMessageBox::Information);
    }
    else
    {
        msgBox.setText(QString("Unable to delete \"%1\"").arg(file.fileName()));
        msgBox.setInformativeText("Please check that the file exists and is not used by another process.");
        msgBox.setIcon(QMessageBox::Warning);
    }
    msgBox.exec();
}

void MainWindow::openInFolder(QFileInfo fileInfo)
{
    QString folderPath = fileInfo.path();
    bool opened = QDesktopServices::openUrl(QUrl(QString("file:///%1").arg(folderPath), QUrl::TolerantMode));
    if (!opened)
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Unable to open \"%1\"").arg(folderPath));
        msgBox.setInformativeText("Please check that the folder exists and is able to be opened.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}
