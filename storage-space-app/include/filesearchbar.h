#ifndef FILESEARCHBAR_H
#define FILESEARCHBAR_H

#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "filesizeinput.h"
#include "searchoptions.h"

class FileSearchBar : public QWidget
{
    Q_OBJECT

public:
    FileSearchBar(QWidget *parent = nullptr);

    SearchOptions options;

signals:
    void searchClicked(SearchOptions options);

private slots:
    void onFileNameContainsChanged(const QString &text);
    void onFileNameExprChanged(const QString &text);
    void onMinInputChanged(qint64 minSize);
    void onMaxInputChanged(qint64 maxSize);
    void onRecursiveChecked(bool checked);
    void onSearchDirChanged(const QString &text);
    void onSearchClicked();
    void onFileDlgBtnClicked();

private:
    QLineEdit *fileNameContainsEdit;
    QLineEdit *fileNameExprEdit;
    QLineEdit *searchDirEdit;
    FileSizeInput *minInput;
    FileSizeInput *maxInput;
    QCheckBox *isRecursiveCheck;
    QPushButton *searchBtn;
    QPushButton *fileDlgBtn;
};

#endif // FILESEARCHBAR_H
