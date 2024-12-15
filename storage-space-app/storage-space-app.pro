QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/fileresult.cpp \
    src/fileresultstable.cpp \
    src/fileresultstabledelegate.cpp \
    src/fileresultstablemodel.cpp \
    src/fileresultstablesortproxy.cpp \
    src/fileresultstablesortproxyworker.cpp \
    src/filesearch.cpp \
    src/filesearchbar.cpp \
    src/filesearchworker.cpp \
    src/filesizeinput.cpp \
    src/mainwindow.cpp \
    src/perlregexvalidator.cpp \
    src/searchoptions.cpp \
    src/settings.cpp \
    src/settingsdialog.cpp \
    src/settingsmanager.cpp

HEADERS += \
    include/fileresult.h \
    include/fileresultstable.h \
    include/fileresultstabledelegate.h \
    include/fileresultstablemodel.h \
    include/fileresultstablesortproxy.h \
    include/fileresultstablesortproxyworker.h \
    include/filesearch.h \
    include/filesearchbar.h \
    include/filesearchworker.h \
    include/filesizeinput.h \
    include/mainwindow.h \
    include/perlregexvalidator.h \
    include/searchoptions.h \
    include/settings.h \
    include/settingsdialog.h \
    include/settingsmanager.h

INCLUDEPATH += \
    include/

RESOURCES += \
    images.qrc
