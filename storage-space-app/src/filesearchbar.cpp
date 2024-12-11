#include "filesearchbar.h"

#include <QFileDialog>
#include <QLabel>
#include <QVBoxLayout>

FileSearchBar::FileSearchBar(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    QHBoxLayout *firstRow = new QHBoxLayout();
    mainLayout->addLayout(firstRow);
    fileNameContainsEdit = new QLineEdit(this);
    fileNameExprEdit = new QLineEdit(this);
    connect(fileNameContainsEdit, SIGNAL(textChanged(QString)), this, SLOT(onFileNameContainsChanged(QString)));
    connect(fileNameExprEdit, SIGNAL(textChanged(QString)), this, SLOT(onFileNameExprChanged(QString)));
    QLabel *fileNameContainsLabel = new QLabel(this);
    QLabel *fileNameExprLabel = new QLabel(this);
    fileNameContainsLabel->setText("Search text:");
    fileNameExprLabel->setText("Search regular expression:");
    firstRow->addWidget(fileNameContainsLabel);
    firstRow->addWidget(fileNameContainsEdit);
    firstRow->addWidget(fileNameExprLabel);
    firstRow->addWidget(fileNameExprEdit);
    QHBoxLayout *secondRow = new QHBoxLayout();
    mainLayout->addLayout(secondRow);
    minInput = new FileSizeInput(this);
    maxInput = new FileSizeInput(this);
    connect(minInput, SIGNAL(fileSizeChanged(qint64)), this, SLOT(onMinInputChanged(qint64)));
    connect(maxInput, SIGNAL(fileSizeChanged(qint64)), this, SLOT(onMaxInputChanged(qint64)));
    QLabel *minLabel = new QLabel(this);
    QLabel *maxLabel = new QLabel(this);
    minLabel->setText("Min:");
    maxLabel->setText("Max:");
    isRecursiveCheck = new QCheckBox(this);
    isRecursiveCheck->setChecked(true);
    QLabel *isRecursiveLabel = new QLabel(this);
    isRecursiveLabel->setText("Recursive:");
    connect(isRecursiveCheck, SIGNAL(toggled(bool)), this, SLOT(onRecursiveChecked(bool)));
    isCaseSensitiveCheck = new QCheckBox(this);
    isCaseSensitiveCheck->setChecked(false);
    QLabel *isCaseSensitiveLabel = new QLabel(this);
    isCaseSensitiveLabel->setText("Match case:");
    connect(isCaseSensitiveCheck, SIGNAL(toggled(bool)), this, SLOT(onCaseSensitiveChecked(bool)));
    secondRow->addWidget(minLabel);
    secondRow->addWidget(minInput);
    secondRow->addWidget(maxLabel);
    secondRow->addWidget(maxInput);
    secondRow->addWidget(isRecursiveLabel);
    secondRow->addWidget(isRecursiveCheck);
    secondRow->addSpacing(12);
    secondRow->addWidget(isCaseSensitiveLabel);
    secondRow->addWidget(isCaseSensitiveCheck);
    secondRow->addStretch();
    QHBoxLayout *thirdRow = new QHBoxLayout();
    mainLayout->addLayout(thirdRow);
    searchDirEdit = new QLineEdit(options.directory.absolutePath(), this);
    connect(searchDirEdit, SIGNAL(textChanged(QString)), this, SLOT(onSearchDirChanged(QString)));
    QLabel *searchDirLabel = new QLabel(this);
    searchDirLabel->setText("Search directory:");
    fileDlgBtn = new QPushButton("Select folder", this);
    connect(fileDlgBtn, SIGNAL(clicked()), this, SLOT(onFileDlgBtnClicked()));
    searchBtn = new QPushButton("Search", this);
    connect(searchBtn, SIGNAL(clicked()), this, SLOT(onSearchClicked()));
    thirdRow->addWidget(searchDirLabel);
    thirdRow->addWidget(searchDirEdit);
    thirdRow->addWidget(fileDlgBtn);
    thirdRow->addWidget(searchBtn);
    mainLayout->addStretch();
}

void FileSearchBar::onFileNameContainsChanged(const QString &text)
{
    options.fileNameContainsTxt = text;
}

void FileSearchBar::onFileNameExprChanged(const QString &text)
{
    options.fileNameExpr = text;
}

void FileSearchBar::onMinInputChanged(qint64 minSize)
{
    options.minFileSizeBytes = minSize;
}

void FileSearchBar::onMaxInputChanged(qint64 maxSize)
{
    options.maxFileSizeBytes = maxSize;
}

void FileSearchBar::onRecursiveChecked(bool checked)
{
    options.isRecursive = checked;
}

void FileSearchBar::onCaseSensitiveChecked(bool checked)
{
    options.isCaseSensitive = checked;
}

void FileSearchBar::onSearchDirChanged(const QString &text)
{
    searchBtn->setDisabled(text.isEmpty());
    options.directory = QDir(text);
}

void FileSearchBar::onSearchClicked()
{
    emit searchClicked(options);
}

void FileSearchBar::onFileDlgBtnClicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
    {
        searchDirEdit->setText(dialog.directory().path());
    }
}
