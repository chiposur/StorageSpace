#include "filesizeinput.h"

#include <float.h>
#include <QHBoxLayout>
#include <QtSystemDetection>

FileSizeInput::FileSizeInput(QWidget *parent)
    : QWidget(parent)
{
    setLayout(new QHBoxLayout());
    fileSizeSpinBox = new QDoubleSpinBox(this);
    fileSizeSpinBox->setFixedWidth(100);
    fileSizeSpinBox->setRange(-1, DBL_MAX);
    fileSizeSpinBox->setValue(-1);
    connect(fileSizeSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
    unitComboBox = new QComboBox(this);
    connect(unitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onFileSizeChanged(int)));
#if (defined (Q_OS_MAC))
    int comboWidth = 62;
#else
    int comboWidth = 46;
#endif
    unitComboBox->setFixedWidth(comboWidth);
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

void FileSizeInput::onValueChanged(double val)
{
    Q_UNUSED(val);
    onFileSizeChanged(unitComboBox->currentIndex());
}
