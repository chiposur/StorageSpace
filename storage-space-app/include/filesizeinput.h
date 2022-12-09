#ifndef FILESIZEINPUT_H
#define FILESIZEINPUT_H

#include <QComboBox>
#include <QDoubleSpinBox>

class FileSizeInput : public QWidget
{
    Q_OBJECT

public:
    FileSizeInput(QWidget *parent = nullptr);

signals:
    void fileSizeChanged(qint64 fileSizeInBytes);

private slots:
    void onFileSizeChanged(int index);

private:
    QDoubleSpinBox *fileSizeSpinBox;
    QComboBox *unitComboBox;
};

#endif // FILESIZEINPUT_H
