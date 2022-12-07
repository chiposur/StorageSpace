#include "filesizeinput.h"

FileSizeInput::FileSizeInput(QWidget *parent)
    : QWidget(parent)
{
    fileSizeSpinBox = new QDoubleSpinBox(this);
    unitComboBox = new QComboBox(this);
    QStringList units;
    units << "KB" << "MB" << "GB" << "TB";
    unitComboBox->addItems(units);
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
