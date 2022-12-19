#include "filesizeinput.h"

#include <float.h>
#include <QHBoxLayout>

FileSizeInput::FileSizeInput(QWidget *parent)
    : QWidget(parent)
{
    setLayout(new QHBoxLayout());
    fileSizeSpinBox = new QDoubleSpinBox(this);
    fileSizeSpinBox->setFixedWidth(100);
    fileSizeSpinBox->setRange(-1, DBL_MAX);
    fileSizeSpinBox->setValue(-1);
    unitComboBox = new QComboBox(this);
    connect(unitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onFileSizeChanged(int)));
    unitComboBox->setFixedWidth(42);
    QStringList units;
    units << "KB" << "MB" << "GB" << "TB";
    unitComboBox->addItems(units);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);
    layout()->addWidget(fileSizeSpinBox);
    layout()->addWidget(unitComboBox);
}

void FileSizeInput::onFileSizeChanged(int index)
{
    double fileSize = fileSizeSpinBox->value();
    switch (index)
    {
        case 0:
        {
            emit fileSizeChanged(fileSize * 1e3);
            break;
        }
        case 1:
        {
            emit fileSizeChanged(fileSize * 1e6);
            break;
        }
        case 2:
        {
            emit fileSizeChanged(fileSize * 1e9);
            break;
        }
        case 3:
        {
            emit fileSizeChanged(fileSize * 1e12);
            break;
        }
        default:
        {
            emit fileSizeChanged(fileSize * 1e3);
        }
    }
}
