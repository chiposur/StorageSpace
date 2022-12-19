#include "settings.h"
#include "settingsdialog.h"

#include <QPushButton>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Settings - Storage Space");
    setWindowIcon(APP_ICON);
    setMinimumWidth(320);
    auto *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    saveWindowGeometryCheck = new QCheckBox("Save window state");
    saveWindowGeometryCheck->setChecked(Settings::getSaveWindowGeometry());
    mainLayout->addWidget(saveWindowGeometryCheck);
    mainLayout->addStretch();
    auto *btnLayout = new QHBoxLayout();
    mainLayout->addLayout(btnLayout);
    btnLayout->addStretch();
    QPushButton *okBtn = new QPushButton("OK", this);
    QPushButton *cancelBtn = new QPushButton("Cancel", this);
    connect(okBtn, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cancelBtn);
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::onOkBtnClicked()
{
    bool saveWindowGeometry = saveWindowGeometryCheck->isChecked();
    Settings::setSaveWindowGeometry(saveWindowGeometry);
    accept();
}
