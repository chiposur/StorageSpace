#include "filesearchbar.h"
#include "perlregexvalidator.h"

#include <QFileDialog>
#include <QLabel>
#include "limits.h"
#include <QVBoxLayout>

FileSearchBar::FileSearchBar(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    constructFirstRow();
    constructSecondRow();
    constructThirdRow();
    mainLayout->addStretch();
}

void FileSearchBar::constructFirstRow()
{
    QHBoxLayout *firstRow = new QHBoxLayout();
    mainLayout->addLayout(firstRow);
    fileNameContainsEdit = new QLineEdit(this);
    fileNameExprEdit = new QLineEdit(this);
    fileNameExprEdit->setValidator(new PerlRegexValidator());
    connect(fileNameContainsEdit, SIGNAL(textChanged(QString)), this, SLOT(onFileNameContainsChanged(QString)));
    connect(fileNameExprEdit, SIGNAL(textChanged(QString)), this, SLOT(onFileNameExprChanged(QString)));
    QLabel *fileNameContainsLabel = new QLabel(this);
    QLabel *fileNameExprLabel = new QLabel(this);
    fileNameContainsLabel->setText("Search text:");
    fileNameExprLabel->setText("Perl-compatible regex:");
    firstRow->addWidget(fileNameContainsLabel);
    firstRow->addWidget(fileNameContainsEdit);
    firstRow->addSpacing(8);
    firstRow->addWidget(fileNameExprLabel);
    firstRow->addWidget(fileNameExprEdit);
}

void FileSearchBar::constructSecondRow()
{
    QHBoxLayout *secondRow = new QHBoxLayout();
    mainLayout->addLayout(secondRow);
    minInput = new FileSizeInput(this);
    maxInput = new FileSizeInput(this);
    depthEdit = new QLineEdit(this);
    depthEdit->setText("-1");
    QIntValidator *depthValidator = new QIntValidator();
    depthValidator->setBottom(-1);
    depthValidator->setTop(INT_MAX);
    depthEdit->setValidator(depthValidator);
    depthEdit->setFixedWidth(90);
    connect(minInput, SIGNAL(fileSizeChanged(qint64)), this, SLOT(onMinInputChanged(qint64)));
    connect(maxInput, SIGNAL(fileSizeChanged(qint64)), this, SLOT(onMaxInputChanged(qint64)));
    connect(depthEdit,SIGNAL(textEdited(const QString &)), this, SLOT(onDepthChanged(const QString &)));
    QLabel *minLabel = new QLabel(this);
    QLabel *maxLabel = new QLabel(this);
    QLabel *depthLabel = new QLabel(this);
    minLabel->setText("Min:");
    maxLabel->setText("Max:");
    depthLabel->setText("Depth:");
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
    secondRow->addWidget(depthLabel);
    secondRow->addWidget(depthEdit);
    secondRow->addWidget(isRecursiveLabel);
    secondRow->addWidget(isRecursiveCheck);
    secondRow->addSpacing(12);
    secondRow->addWidget(isCaseSensitiveLabel);
    secondRow->addWidget(isCaseSensitiveCheck);
    secondRow->addStretch();
}

void FileSearchBar::constructThirdRow()
{
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

void FileSearchBar::onDepthChanged(const QString &depth)
{
    bool ok;
    qint64 convertedDepth = depth.toLongLong(&ok);
    if (!ok || depth.isEmpty())
    {
        convertedDepth = -1;
    }
    options.maxDepth = convertedDepth;
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
