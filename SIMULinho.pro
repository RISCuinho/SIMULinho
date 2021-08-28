TEMPLATE = subdirs

CONFIG += c++17

CONFIG += no_keywords
unix:CONFIG += link_pkgconfig
unix:PKGCONFIG += dbus-cxx-qt-2.0

DEFINES += _SIMULINHO_
# Usado pelo RTL e ferramentas de simulação
DEFINES += __SIMULINHO_DUMP__

SUBDIRS = \
    SIMULinho_LIB \
    SIMULinho_VPI \
    SIMULinho_UI

SIMULinho_LIB.subdir = SIMULinho_LIB

SIMULinho_UI.depend += SIMULinho_LIB
SIMULinho_UI.subdir += SIMULinho_UI

SIMULinho_VPI.subdir = SIMULinho_VPI
SIMULinho_VPI.depend += SIMULinho_LIB
SIMULinho_VPI.depend += SIMULinho_UI

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/SIMULinho_LIB/release/ -lSIMULinho_LIB
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/SIMULinho_LIB/debug/ -lSIMULinho_LIB
else:unix: LIBS += -L$$OUT_PWD/SIMULinho_LIB/ -lSIMULinho

INCLUDEPATH += $$PWD/SIMULinho_LIB
DEPENDPATH += $$PWD/SIMULinho_LIB

RESOURCES += \
    HowtoExecQTCreator.md \
    TODO.md \
    comms.pri \
    temp.txt \
    COMMAND_GLOSSARY.md \
    simulinho.v

modulevpi.name = Verilognize Module VPI
modulevpi.commands = $(MAKE) -C SIMULinho_VPI compiler_modulevpi_make_all

QMAKE_EXTRA_TARGETS += modulevpi

verilognize_vvp.name = Verilognize VVP
verilognize_vvp.depends  = SIMULinho_LIB SIMULinho_VPI modulevpi
verilognize_vvp.variable_out = VERILOGNIZERS_VVP
verilognize_vvp.commands  = iverilog \
                                -I $$OUT_PWD/SIMULinho_LIB/ -L . \
                                -m $$OUT_PWD/SIMULinho_VPI/simulinho \
                                -o simulinho.vvp $${_PRO_FILE_PWD_}/simulinho.v
QMAKE_EXTRA_TARGETS += verilognize_vvp

verilognize.name = Verilognize
verilognize.depends  = verilognize_vvp
verilognize.commands = -echo "V E R I L O G N I Z E" &&
verilognize.commands += vvp -v simulinho.vvp
QMAKE_EXTRA_TARGETS += verilognize


