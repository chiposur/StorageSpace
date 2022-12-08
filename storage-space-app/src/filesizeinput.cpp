#include <float.h>
#include <QHBoxLayout>

#include "filesizeinput.h"

FileSizeInput::FileSizeInput(QWidget *parent)
    : QWidget(parent)
{
    setLayout(new QHBoxLayout());
    fileSizeSpinBox = new QDoubleSpinBox(this);
    fileSizeSpinBox->setFixedWidth(100);
    fileSizeSpinBox->setRange(-1, DBL_MAX);
    fileSizeSpinBox->setValue(-1);
    unitComboBox = new QComboBox(this);
    unitComboBox->setFixedWidth(40);
    QStringList units;
    units << "KB" << "MB" << "GB" << "TB";
    unitComboBox->addItems(units);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);
    layout()->addWidget(fileSizeSpinBox);
    layout()->addWidget(unitComboBox);
}

void FileSizeInput::onFileSizeChanged(double fileSize)
{
    switch (unitComboBox->currentIndex())
    {
    case 0:
        emit fileSizeChanged(fileSize * 1000);
    case 1:
        emit fileSizeChanged(fileSize * 1000000);
    case 2:
        emit fileSizeChanged(fileSize * 1000000000);
    case 3:
        emit fileSizeChanged(fileSize * 1000000000000);
    default:
        emit fileSizeChanged(fileSize * 1000);
    }
}
