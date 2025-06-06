QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += precompiled_header
PRECOMPILED_HEADER = precompiled.h

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Graphs/dirgraph.cpp \
    Graphs/graph.cpp \
    Graphs/udirgraph.cpp \
    Graphs/upseudograph.cpp \
    Graphs/wdirgraph.cpp \
    Overrided/console.cpp \
    Overrided/dialog.cpp \
    graphmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp

HEADERS += \
    Graphs/dirgraph.h \
    Graphs/graph.h \
    Graphs/udirgraph.h \
    Graphs/upseudograph.h \
    Graphs/wdirgraph.h \
    Overrided/console.h \
    Overrided/dialog.h \
    general.h \
    graphmanager.h \
    mainwindow.h \
    parser.h \
    precompiled.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc

DISTFILES += $$PWD/hystory.txt

