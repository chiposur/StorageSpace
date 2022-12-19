#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    static bool getSaveWindowGeometry() { return saveWindowGeometry; }
    static void setSaveWindowGeometry(bool saveGeometry) { saveWindowGeometry = saveGeometry; }

private:
    static bool saveWindowGeometry;
};

#endif // SETTINGS_H
