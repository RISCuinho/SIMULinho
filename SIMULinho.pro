TEMPLATE = subdirs

CONFIG += c++11

DEFINES += SIMULINHO

SUBDIRS = SIMULinho_VPI \
    SIMULinho_UI

SIMULinho_VPI.subdir = SIMULinho_VPI
SIMULinho_VPI.depend = SIMULinho_UI

# Usado pelo RTL e ferramentas de simulação
DEFINES += __SIMULINHO_DUMP__


DISTFILES += \
    comms.pri \
    temp.txt \
    COMMAND_GLOSSARY.md \
    simulinho.v



verilognize_vvp.name = Verilognize VVP
verilognize_vvp.depends  = SIMULinho_VPI
verilognize_vvp.variable_out = VERILOGNIZERS_VVP
verilognize_vvp.commands  = iverilog -L . -m simulinho_vpi \
                                 -o simulinho.vvp $${_PRO_FILE_PWD_}/simulinho.v
QMAKE_EXTRA_TARGETS += verilognize_vvp

verilognize.name = Verilognize
verilognize.depends  = verilognize_vvp
verilognize.commands = -echo "V E R I L O G N I Z E" &&
verilognize.commands += vvp -v simulinho.vvp
QMAKE_EXTRA_TARGETS += verilognize

