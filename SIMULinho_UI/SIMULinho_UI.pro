#-------------------------------------------------
#
# Project created by QtCreator 2021-08-17T20:52:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z

unix:CONFIG += link_pkgconfig
unix:PKGCONFIG += dbus-cxx-2.0
unix:PKGCONFIG += dbus-cxx-qt-2.0

DEPENDPATH += /usr/local/include/dbus-cxx-2.0
DEPENDPATH += /usr/local/include/sigc++-3.0

INCLUDEPATH += /usr/local/include/dbus-cxx-2.0
INCLUDEPATH += /usr/local/include/sigc++-3.0
INCLUDEPATH += /usr/local/lib/sigc++-3.0/include/

TARGET = SIMULinho
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        simulinho.cpp \
        main.cpp \
    memorytable.cpp

HEADERS += \
    simulinho.h \
    memorytable.h

FORMS += \
    simulinho.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SIMULinho_LIB/release/ -lSIMULinho_LIB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SIMULinho_LIB/debug/ -lSIMULinho_LIB
else:unix: LIBS += -L$$OUT_PWD/../SIMULinho_LIB/ -lSIMULinho

INCLUDEPATH += $$PWD/../SIMULinho_LIB
DEPENDPATH += $$PWD/../SIMULinho_LIB

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EquipoGraph_LIB/release/ -lEquipoGraph
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EquipoGraph_LIB/debug/ -lEquipoGraph
else:unix: LIBS += -L$$OUT_PWD/../EquipoGraph_LIB/ -lEquipoGraph

INCLUDEPATH += $$PWD/../EquipoGraph_LIB
DEPENDPATH += $$PWD/../EquipoGraph_LIB

RESOURCES += \
    memory.qrc

