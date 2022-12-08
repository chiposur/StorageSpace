QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    src/fileresult.cpp \
    src/filesearch.cpp \
    src/filesearchbar.cpp \
    src/filesearchworker.cpp \
    src/filesizeinput.cpp \
    src/mainwindow.cpp \
    src/searchoptions.cpp

HEADERS += \
    include/fileresult.h \
    include/filesearch.h \
    include/filesearchbar.h \
    include/filesearchworker.h \
    include/filesizeinput.h \
    include/mainwindow.h \
    include/searchoptions.h

INCLUDEPATH += \
    include/
