#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QByteArray>

class SettingsManager
{
public:
    static SettingsManager *getInstance();
    void readSettings();
    void saveSettings();
    QByteArray readGeometry();
    void saveGeometry(QByteArray geometry);

private:
    SettingsManager();
};

#endif // SETTINGSMANAGER_H
