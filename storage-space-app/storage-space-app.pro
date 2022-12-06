QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/filesearch.cpp \
    src/mainwindow.cpp \
    src/searchoptions.cpp

HEADERS += \
    include/filesearch.h \
    include/mainwindow.h \
    include/searchoptions.h

INCLUDEPATH += \
    include/
