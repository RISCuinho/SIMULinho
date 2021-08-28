#-------------------------------------------------
#
# Project created by QtCreator 2021-08-17T18:41:50
#
#-------------------------------------------------

QT       -= gui

TARGET = simulinhoVPI
TEMPLATE = lib

CONFIG += dll
CONFIG += c++17

CONFIG += no_keywords

#unix:CONFIG += link_pkgconfig
#unix:PKGCONFIG += dbus-cxx-2.0

//VERSION = 0.0.1

DEFINES += SIMULINHO_VPI_LIBRARY

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
        simulinhovpi.cpp \
        simulinho.cpp

HEADERS += \
        simulinhovpi.h \
        simulinho.h

DEPENDPATH += /usr/local/include/iverilog
DEPENDPATH += $$PWD/../SIMULinho_LIB

INCLUDEPATH += /usr/local/include/iverilog
INCLUDEPATH += $$PWD/../SIMULinho_LIB

unix:!macx: LIBS += -L/usr/local/lib/ -lvpi -lveriuser

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SIMULinho_LIB/release/ -lSIMULinho
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SIMULinho_LIB/debug/ -lSIMULinho
else:unix: LIBS += -L$$OUT_PWD/../SIMULinho_LIB/ -lSIMULinho


unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCE_modulevpi = simulinho.o
modulevpi.name = Shared VPI Object Simulinho VPI
modulevpi.input = SOURCE_modulevpi
##modulevpi.dependency_type = TYPE_C
modulevpi.depends = simulinhovpi.o
modulevpi.output = ${QMAKE_FILE_IN_BASE}.vpi
#  g++ -o simulinho_vpi.so --shared  simulinho_vpi.o qrc_qml.o simulinho.o  -L/usr/lib/i386-linux-gnu -L/usr/local/lib/ -lvpi -lveriuser -lQt5Quick -lQt5Gui -lQt5Qml -lQt5Network -lQt5Core -lGL -lpthread
modulevpi.commands = $${QMAKE_CXX} -o ${QMAKE_FILE_OUT} \
                                 --shared $(LDFLAGS) \
                                  simulinhovpi.o ${QMAKE_FILE_IN} \
                                 $(LIBS)
QMAKE_EXTRA_COMPILERS += modulevpi

