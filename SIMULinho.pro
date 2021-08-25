TEMPLATE = subdirs

CONFIG += c++17

CONFIG += no_keywords
unix:CONFIG += link_pkgconfig
unix:PKGCONFIG += dbus-cxx-qt-2.0

DEFINES += _SIMULINHO_
# Usado pelo RTL e ferramentas de simulação
DEFINES += __SIMULINHO_DUMP__

SUBDIRS = SIMULinho_VPI \
    SIMULinho_UI \
    SIMULinho_LIB

SIMULinho_LIB.subdir = SIMULinho_LIB

SIMULinho_UI.subdir = SIMULinho_UI
SIMULinho_UI.depend += SIMULinho_LIB

SIMULinho_VPI.subdir = SIMULinho_VPI
SIMULinho_VPI.depend = SIMULinho_UI
SIMULinho_VPI.depend += SIMULinho_LIB

RESOURCES += \
    TODO.md \
    comms.pri \
    temp.txt \
    COMMAND_GLOSSARY.md \
    simulinho.v

modulevpi.name = Verilognize Module VPI
modulevpi.commands = $(MAKE) -C SIMULinho_VPI compiler_modulevpi_make_all

QMAKE_EXTRA_TARGETS += modulevpi

verilognize_vvp.name = Verilognize VVP
verilognize_vvp.depends  = SIMULinho_VPI modulevpi
verilognize_vvp.variable_out = VERILOGNIZERS_VVP
verilognize_vvp.commands  = iverilog -L . -m $$OUT_PWD/SIMULinho_VPI/simulinho \
                                 -o simulinho.vvp $${_PRO_FILE_PWD_}/simulinho.v
QMAKE_EXTRA_TARGETS += verilognize_vvp

verilognize.name = Verilognize
verilognize.depends  = verilognize_vvp
verilognize.commands = -echo "V E R I L O G N I Z E" &&
verilognize.commands += vvp -v simulinho.vvp
QMAKE_EXTRA_TARGETS += verilognize

