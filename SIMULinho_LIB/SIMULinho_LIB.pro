#-------------------------------------------------
#
# Project created by QtCreator 2021-08-17T21:37:00
#
#-------------------------------------------------

QT       -= gui

CONFIG += c++1z

TARGET = SIMULinho

TEMPLATE = lib

##VERSION = 0.0.1

DEFINES += SIMULINHO_LIBRARY

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
        simulinhodbusclient.cpp \
        simulinhodbusserver.cpp

HEADERS += \
        simulinho_lib_global.h  \
        simulinhoclient.h \
        simulinhodbus.h \
        simulinhodbusclient.h \
        simulinhodbusserver.h \
        simulinhoserver.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DEPENDPATH += /usr/local/include/dbus-cxx-2.0
DEPENDPATH += /usr/local/include/sigc++-3.0

INCLUDEPATH += /usr/local/include/dbus-cxx-2.0
INCLUDEPATH += /usr/local/include/sigc++-3.0
INCLUDEPATH += /usr/local/lib/sigc++-3.0/include/

DISTFILES += \
    SIMULinho_dbus.xml

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += dbus-cxx-2.0
unix: PKGCONFIG += dbus-cxx-glib-2.0
unix: PKGCONFIG += dbus-cxx-qt-2.0


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/i386-linux-gnu/release/ -lglib-2.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/lib/i386-linux-gnu/debug/ -lglib-2.0
else:unix: LIBS += -L$$PWD/../../../../../../usr/lib/i386-linux-gnu/ -lglib-2.0

INCLUDEPATH += $$PWD/../../../../../../usr/lib/i386-linux-gnu/glib-2.0/include
DEPENDPATH += $$PWD/../../../../../../usr/lib/i386-linux-gnu/glib-2.0/include
