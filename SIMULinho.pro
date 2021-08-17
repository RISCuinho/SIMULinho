TEMPLATE = app

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTWidgetsApplication

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

## TODO: Verificar problema com "undefined symbol: qt_version_tag." quando no vvp por hora a correção é usar -DQT_NO_VERSION_TAGGING
#DEFINES += QT_NO_VERSION_TAGGING

# Informa que as bibliotecas do RISCuinho quando for o caso serão
# :compartilhadas para uso externo
DEFINES += SIMULINHO_SHAREDLIB

# Usado pelo RTL e ferramentas de simulação
DEFINES += __SIMULINHO_DUMP__

SOURCES += \
    simulinho_base_app.cpp \
    simulinho_window.cpp \
    simulinho_vpi.cpp

RESOURCES +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    simulinho_base_app.h \
    simulinho_window.h \
    simulinho_vpi.h

DISTFILES += \
    comms.pri \
    temp.txt \
    COMMAND_GLOSSARY.md \
    simulinho.v

FORMS += \
    simulinho_window.ui

unix:!macx: LIBS += -L/usr/lib/i386-linux-gnu
unix:!macx: LIBS += -L/usr/local/lib/ -lvpi -lveriuser

INCLUDEPATH += /usr/local/lib/ivl/include
INCLUDEPATH += /usr/local/include/iverilog

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libveriuser.a
unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libvpi.a

DEPENDPATH += /usr/local/lib/ivl/include
DEPENDPATH += /usr/local/include/iverilog
DEPENDPATH += /usr/lib/i386-linux-gnu
DEPENDPATH += $$PWD/''

SOURCE_OBJVPI = simulinho_vpi.o
objvpi.name = Shared VPI Object Simulinho VPI
objvpi.input = SOURCE_OBJVPI
objvpi.dependency_type = TYPE_C
objvpi.depends =  mocables moc_simulinho_window.o simulinho_vpi.o simulinho_base_app.o simulinho_window.o
objvpi.output = ${QMAKE_FILE_IN_BASE}.vpi
#  g++ -o simulinho_vpi.so --shared  simulinho_vpi.o qrc_qml.o simulinho.o  -L/usr/lib/i386-linux-gnu -L/usr/local/lib/ -lvpi -lveriuser -lQt5Quick -lQt5Gui -lQt5Qml -lQt5Network -lQt5Core -lGL -lpthread
objvpi.commands = $${QMAKE_CXX} -o ${QMAKE_FILE_OUT} \
                                 --shared $(LDFLAGS) \
                                 moc_simulinho_window.o simulinho_window.o simulinho_base_app.o \
                                 ${QMAKE_FILE_IN} \
                                 $(LIBS)
QMAKE_EXTRA_COMPILERS += objvpi

verilognize_vvp.name = Verilognize VVP
verilognize_vvp.depends  = compiler_objvpi_clean
verilognize_vvp.depends += compiler_objvpi_make_all
verilognize_vvp.variable_out = VERILOGNIZERS_VVP
verilognize_vvp.commands  = iverilog -L . -m simulinho_vpi \
                                 -o simulinho.vvp $${_PRO_FILE_PWD_}/simulinho.v
QMAKE_EXTRA_TARGETS += verilognize_vvp

verilognize.name = Verilognize
verilognize.depends  = verilognize_vvp
verilognize.commands = -echo "V E R I L O G N I Z E" &&
verilognize.commands += vvp -v simulinho.vvp
QMAKE_EXTRA_TARGETS += verilognize

