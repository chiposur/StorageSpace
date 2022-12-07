#ifndef FILESEARCHBAR_H
#define FILESEARCHBAR_H

#include <QLineEdit>
#include <QWidget>

#include "searchoptions.h"

class FileSearchBar : public QWidget
{
    Q_OBJECT

public:
    FileSearchBar(QWidget *parent = nullptr);

    SearchOptions options;

private:
    QLineEdit *fileNameContainsEdit;
    QLineEdit *fileNameExprEdit;
};

#endif // FILESEARCHBAR_H
