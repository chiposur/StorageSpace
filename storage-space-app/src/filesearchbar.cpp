#include "filesearchbar.h"

#include <QLabel>
#include <QVBoxLayout>

FileSearchBar::FileSearchBar(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    QHBoxLayout *fileNameRow = new QHBoxLayout();
    mainLayout->addLayout(fileNameRow);
    fileNameContainsEdit = new QLineEdit(this);
    fileNameExprEdit = new QLineEdit(this);
    QLabel *fileNameContainsLabel = new QLabel(this);
    QLabel *fileNameExprLabel = new QLabel(this);
    fileNameContainsLabel->setText("Search text:");
    fileNameExprLabel->setText("Search regular expression:");
    fileNameRow->addWidget(fileNameContainsLabel);
    fileNameRow->addWidget(fileNameContainsEdit);
    fileNameRow->addWidget(fileNameExprLabel);
    fileNameRow->addWidget(fileNameExprEdit);
    mainLayout->addStretch();
}
