#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QIcon>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);

private slots:
    void onOkBtnClicked();

private:
    QCheckBox *saveWindowGeometryCheck;
    const QIcon APP_ICON = QIcon(QPixmap(":/images/app-icon.ico"));
};

#endif // SETTINGSDIALOG_H
