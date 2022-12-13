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
    qRegisterMetaType<Qt::SortOrder>("Qt::SortOrder");
    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");
    setWindowTitle("Storage Space");
    setWindowIcon(APP_ICON);
    setMinimumSize(QSize(800, 600));
    setCentralWidget(new QWidget());
    mainLayout = new QVBoxLayout();
    centralWidget()->setLayout(mainLayout);
    searchBar = new FileSearchBar(this);
    connect(searchBar, SIGNAL(searchClicked(SearchOptions)), this, SLOT(onSearchClicked(SearchOptions)));
    mainLayout->addWidget(searchBar);
    resultsCountLabel = new QLabel(this);
    resultsTimeLabel = new QLabel(this);
    QHBoxLayout *resultInfoRow = new QHBoxLayout();
    resultInfoRow->addWidget(resultsCountLabel);
    resultInfoRow->addStretch();
    resultInfoRow->addWidget(resultsTimeLabel);
    mainLayout->addLayout(resultInfoRow);
    resultsTable = new FileResultsTable(this);
    mainLayout->addWidget(resultsTable);
    FileSearchWorker *worker = new FileSearchWorker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::startSearch, worker, &FileSearchWorker::search);
    connect(worker, &FileSearchWorker::resultsReady, this, &MainWindow::onSearchFinished);
    workerThread.start();
    resultsTimer = new QTimer(this);
    sortTimer = new QTimer(this);
    connect(resultsTimer, SIGNAL(timeout()), this, SLOT(onResultsTimerTick()));
    connect(sortTimer, SIGNAL(timeout()), this, SLOT(onSortTimerTick()));
    connect(resultsTable, SIGNAL(sortStarted()), this, SLOT(onSortStarted()));
    connect(resultsTable, SIGNAL(sortFinished()), this, SLOT(onSortFinished()));
    connect(resultsTable, SIGNAL(openInFolder(QFileInfo)), this, SLOT(onOpenInFolder(QFileInfo)));
    connect(resultsTable, SIGNAL(deleteFile(QFile&,QDir)), this, SLOT(onDeleteFile(QFile&,QDir)));
}

void MainWindow::onSearchClicked(SearchOptions options)
{
    resultsTable->setDisabled(true);
    results.clear();
    resultsTable->setItems(results);
    searchBar->setDisabled(true);
    resultsCountLabel->setText("Searching.");
    resultsTimeMs = 0;
    emit startSearch(options);
    resultsTimer->start(RESULTS_TIMER_INTERVAL_MS);
}

void MainWindow::onSortStarted()
{
    sortTimeMs = 0;
    sortTimer->start(SORT_TIMER_INTERVAL_MS);
}

void MainWindow::onSearchFinished(const QVector<FileResult> &results)
{
    searchRun = true;
    resultsTable->setEnabled(true);
    resultsTimer->stop();
    searchBar->setEnabled(true);
    this->results = results;
    resultsTimeLabel->clear();
    resultsCountLabel->setText(resultsString());
    resultsTable->setItems(results);
}

void MainWindow::onSortFinished()
{
    sortTimer->stop();
    resultsCountLabel->setText(resultsString());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    workerThread.exit();
    QMainWindow::closeEvent(event);
}

void MainWindow::onDeleteFile(QFile &file, QDir dir)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirm deletion");
    msgBox.setWindowIcon(APP_ICON);
    QString warningMsg =
        QString("This will permanently delete \"%1\". Are you sure you want to continue?").arg(file.fileName());
    msgBox.setText(warningMsg);
    msgBox.setIcon(QMessageBox::Icon::Warning);
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    if (msgBox.exec() == QMessageBox::No)
    {
        return;
    }
    msgBox.setStandardButtons(QMessageBox::Ok);
    if (file.remove())
    {
        QString absoluteFilePath = dir.absoluteFilePath(file.fileName());
        int index = -1;
        for (int i = 0; i < results.count(); ++i)
        {
            if (results.at(i).path == absoluteFilePath)
            {
                index = i;
                break;
            }
        }
        if (index > -1)
        {
            results.removeAt(index);
            resultsTable->setItems(results);
            resultsTable->update();
        }
        msgBox.setWindowTitle("Delete successful");
        msgBox.setText(QString("Successfully deleted \"%1\"").arg(file.fileName()));
        msgBox.setIcon(QMessageBox::Information);
    }
    else
    {
        msgBox.setWindowTitle("Delete failed");
        msgBox.setText(QString("Unable to delete \"%1\"").arg(file.fileName()));
        msgBox.setInformativeText("Please check that the file exists and is not used by another process.");
    }
    msgBox.exec();
}

void MainWindow::onOpenInFolder(QFileInfo fileInfo)
{
    QString folderPath = fileInfo.path();
    bool opened = QDesktopServices::openUrl(QUrl(QString("file:///%1").arg(folderPath), QUrl::TolerantMode));
    if (!opened)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Open in folder failed");
        msgBox.setWindowIcon(APP_ICON);
        msgBox.setText(QString("Unable to open \"%1\"").arg(folderPath));
        msgBox.setInformativeText("Please check that the folder exists and is able to be opened.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}

void MainWindow::onResultsTimerTick()
{
    resultsTimeMs += RESULTS_TIMER_INTERVAL_MS;
    int ellipsisCount = resultsTimeMs / 1000 % 3;
    QString searchingTxt;
    switch (ellipsisCount)
    {
        case 0:
        {
            searchingTxt = "Searching.";
            break;
        }
        case 1:
        {
            searchingTxt = "Searching..";
            break;
        }
        case 2:
        {
            searchingTxt = "Searching...";
            break;
        }
    }
    resultsCountLabel->setText(searchingTxt);
    resultsCountLabel->update();
    resultsTimeLabel->setText(resultsTimeString());
    resultsTimeLabel->update();
}

void MainWindow::onSortTimerTick()
{
    sortTimeMs += SORT_TIMER_INTERVAL_MS;
    int ellipsisCount = sortTimeMs / 1000 % 3;
    QString sortingTxt;
    switch (ellipsisCount)
    {
        case 0:
        {
            sortingTxt = "Sorting.";
            break;
        }
        case 1:
        {
            sortingTxt = "Sorting..";
            break;
        }
        case 2:
        {
            sortingTxt = "Sorting...";
            break;
        }
    }
    resultsCountLabel->setText(sortingTxt);
    resultsCountLabel->update();
}

QString MainWindow::resultsTimeString()
{
    if (resultsTimeMs == 0)
    {
        return QString("<%1ms").arg(QString::number(RESULTS_TIMER_INTERVAL_MS).rightJustified(3, '0'));
    }
    int hours = resultsTimeMs / (1000 * 60 * 60);
    int minutes = resultsTimeMs / (1000 * 60);
    int seconds = resultsTimeMs / 1000;
    QString hoursStr = QString::number(hours);
    QString minutesStr = QString::number(minutes % 60).rightJustified(2, '0');
    QString secondsStr = QString::number(seconds % 60).rightJustified(2, '0');
    QString msStr = QString::number(resultsTimeMs % 1000).rightJustified(3, '0');
    return QString("%1:%2:%3:%4").arg(hoursStr, minutesStr, secondsStr, msStr);
}

QString MainWindow::resultsString()
{
    if (!searchRun)
    {
        return "";
    }
    return QString("%1 results found in %2").
        arg(QString::number(results.count()), resultsTimeString());
}
