#include <QCoreApplication>
#include <QSettings>

#include "settings.h"
#include "settingsmanager.h"

SettingsManager::SettingsManager()
{
    QCoreApplication::setOrganizationName("chiposur");
    QCoreApplication::setApplicationName("Storage Space");
}

SettingsManager::~SettingsManager()
{
}

SettingsManager *SettingsManager::getInstance()
{
    static SettingsManager singleton;
    return &singleton;
}

void SettingsManager::readSettings()
{
    QSettings settings;
    bool saveWindowGeometry =
        settings.value("saveWindowGeometry", false).toBool();
    Settings::setSaveWindowGeometry(saveWindowGeometry);
}

void SettingsManager::saveSettings()
{
    QSettings settings;
    settings.setValue("saveWindowGeometry", Settings::getSaveWindowGeometry());
}

QByteArray SettingsManager::readGeometry()
{
    QSettings settings;
    return settings.value("windowGeometry", QByteArray()).toByteArray();
}

void SettingsManager::saveGeometry(QByteArray geometry)
{
    QSettings settings;
    settings.setValue("windowGeometry", geometry);
}
