#include "filesearchworker.h"
#include "mainwindow.h"
#include "settings.h"
#include "settingsdialog.h"
#include "settingsmanager.h"

#include <QAction>
#include <QDate>
#include <QDesktopServices>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMetaType>
#include <QUrl>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<SearchOptions>("SearchOptions");
    qRegisterMetaType<FileResult>("FileResult");
    qRegisterMetaType<QVector<FileResult>>("QVector<FileResult>");
    qRegisterMetaType<Qt::SortOrder>("Qt::SortOrder");
    qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");
    qRegisterMetaType<QAbstractItemModel::LayoutChangeHint>("QAbstractItemModel::LayoutChangeHint");
    setWindowTitle("Storage Space");
    setWindowIcon(APP_ICON);
    setMinimumSize(QSize(800, 600));
    SettingsManager::getInstance()->readSettings();
    if (Settings::getSaveWindowGeometry())
    {
        restoreGeometry(SettingsManager::getInstance()->readGeometry());
    }
    createMenuBar();
    createCentralWidget();
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

void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("File", menuBar);
    menuBar->addMenu(fileMenu);
    QAction *settingsAction = new QAction("Settings", fileMenu);
    QAction *exitAction = new QAction("Exit", fileMenu);
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(onSettingsActionTriggered()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(onExitActionTriggered()));
    fileMenu->addAction(settingsAction);
    fileMenu->addAction(exitAction);
    QMenu *helpMenu = new QMenu("Help", menuBar);
    QAction *aboutAction = new QAction("About", helpMenu);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(onAboutActionTriggered()));
    helpMenu->addAction(aboutAction);
    menuBar->addMenu(helpMenu);
    setMenuBar(menuBar);
}

void MainWindow::onSettingsActionTriggered()
{
    SettingsDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        SettingsManager::getInstance()->saveSettings();
    }
}

void MainWindow::onExitActionTriggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Exit Storage Space");
    msgBox.setWindowIcon(APP_ICON);
    QString warningMsg = "Are you sure you want to exit?";
    msgBox.setText(warningMsg);
    msgBox.setIcon(QMessageBox::Icon::Warning);
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if (msgBox.exec() == QMessageBox::Yes)
    {
        close();
    }
}

void MainWindow::onAboutActionTriggered()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(APP_ICON);
    msgBox.setWindowTitle("About - Storage Space");
    QString text = QString("Storage Space\nCopyright (c) %1 Chip Osur").arg(QDate::currentDate().year());
    msgBox.setText(text);
    QString informativeTxt =
        "Native GUI for finding large files and cleaning up storage space. "
        "Allows for recursively searching directories for files that match the specified search criteria, "
        "opening up results in folder and deleting from disk.";
    msgBox.setInformativeText(informativeTxt);
    msgBox.exec();
}

void MainWindow::createCentralWidget()
{
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
    resultsTable = new FileResultsTable(&results, this);
    mainLayout->addWidget(resultsTable);
}

void MainWindow::onSearchClicked(SearchOptions options)
{
    resultsTable->setDisabled(true);
    resultsTable->setRows(QVector<FileResult>());
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
    resultsTable->setRows(results);
    resultsTable->setEnabled(true);
    resultsTimer->stop();
    searchBar->setEnabled(true);
    resultsTimeLabel->clear();
    resultsInfo = resultsString();
    resultsCountLabel->setText(resultsInfo);
}

void MainWindow::onSortFinished()
{
    sortTimer->stop();
    resultsCountLabel->setText(resultsInfo);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    workerThread.exit();
    if (Settings::getSaveWindowGeometry())
    {
        QByteArray geometry = saveGeometry();
        SettingsManager::getInstance()->saveGeometry(geometry);
    }
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
            resultsTable->deleteRow(index);
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

QString MainWindow::resultsTimeString() const
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

QString MainWindow::resultsString() const
{
    if (!searchRun)
    {
        return "";
    }
    return QString("%1 results found in %2").
        arg(QString::number(results.count()), resultsTimeString());
}
