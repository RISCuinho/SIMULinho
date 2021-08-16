QT += quick
CONFIG += c++11
CONFIG += create_prl
CONFIG -= qml_debug
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

## TODO: Verificar problema com "undefined symbol: qt_version_tag." quando no vvp por hora a correção é usar -DQT_NO_VERSION_TAGGING
DEFINES += QT_NO_VERSION_TAGGING

# Informa que as bibliotecas do RISCuinho quando for o caso serão
# :compartilhadas para uso externo
DEFINES += SIMULINHO_SHAREDLIB

# Usado pelo RTL e ferramentas de simulação
DEFINES += __SIMULINHO_DUMP__

#DEFINES -= QT_QML_DEBUG_NO_WARNING
#DEFINES -= QT_QML_DEBUG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    simulinho.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    simulinho_global.h \
    simulinho.h \
    simulinho_vpi.h


DISTFILES += \
    comms.pri \
    temp.txt \
    COMMAND_GLOSSARY.md \
    simulinho.v

unix:!macx: LIBS += -L/usr/lib/i386-linux-gnu
unix:!macx: LIBS += -lvpi
unix:!macx: LIBS += -lveriuser

#INCLUDEPATH += /usr/lib/i386-linux-gnu
INCLUDEPATH += /usr/local/include/iverilog/
INCLUDEPATH += $$PWD/''

DEPENDPATH += /usr/local/include/iverilog/
DEPENDPATH += /usr/lib/i386-linux-gnu
DEPENDPATH += $$PWD/''

unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libveriuser.a
unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libvpi.a

## https://stackoverflow.com/questions/27683777/how-to-specify-compiler-flag-to-a-single-source-file-with-qmake
## http://doc.qt.io/qt-5/qmake-advanced-usage.html#adding-compilers
## configura riscuinho.cpp para ser compilado adequadamente para o vpi
SOURCE_OBJVPI = simulinho_vpi.cpp
objvpi.name = Shared VPI Object Simulinho VPI
objvpi.input = SOURCE_OBJVPI
objvpi.dependency_type = TYPE_C
objvpi.depends = simulinho.o qrc_qml.o
#objvpi.variable_out = OBJECTS
objvpi.output = ${QMAKE_FILE_IN_BASE}.so
objvpi.clean = ${QMAKE_FILE_IN_BASE}.*
objvpi.commands = $${QMAKE_CXX} -c $(CXXFLAGS) -fPIC \
                                ${INCPATH} \
                                -fstack-protector-strong \
                                -Wformat -Werror=format-security -Wextra -Wshadow \
                                -fdebug-prefix-map=/build/iverilog-3pPO9t/iverilog-10.1=. \
                                -g \
                                -o ${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)} \
                                ${QMAKE_FILE_IN}
objvpi.commands += &&
objvpi.commands += $${QMAKE_CXX} --shared $(CXXFLAGS) \
                                 $(LIBS) \
                                 simulinho.o qrc_qml.o \
                                 -o ${QMAKE_FILE_OUT} \
                                 ${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
QMAKE_EXTRA_COMPILERS += objvpi

SOURCE_MODULEVPI = simulinho_vpi.so
#modulevpi.name = Gera o módulo simulinho_vpi.vpi com base no simulinho_vpi.so
modulevpi.input = SOURCE_MODULEVPI
#modulevpi.dependency_type = TYPE_C
modulevpi.depends = compiler_objvpi_make_all
modulevpi.output = ${QMAKE_FILE_IN_BASE}.vpi
modulevpi.clean  = ${QMAKE_FILE_IN_BASE}.vpi
modulevpi.clean += ${QMAKE_FILE_IN_BASE}.vpi.debug
modulevpi.commands = cp ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
modulevpi.commands += &&
modulevpi.commands += objcopy --only-keep-debug ${QMAKE_FILE_OUT} ${QMAKE_FILE_OUT}.debug
modulevpi.commands += &&
modulevpi.commands += objcopy --strip-debug ${QMAKE_FILE_OUT}
modulevpi.commands += &&
modulevpi.commands += objcopy --add-gnu-debuglink=${QMAKE_FILE_OUT}.debug ${QMAKE_FILE_OUT}
QMAKE_EXTRA_COMPILERS += modulevpi

verilognize_vvp.name = VerilognizeVVP
verilognize_vvp.depends  = compiler_objvpi_clean
verilognize_vvp.depends += compiler_modulevpi_clean
verilognize_vvp.depends += compiler_objvpi_make_all
verilognize_vvp.depends += compiler_modulevpi_make_all
verilognize_vvp.variable_out = VERILOGNIZERS_VVP
verilognize_vvp.commands  = iverilog -o simulinho.vvp $${_PRO_FILE_PWD_}/simulinho.v
verilognize_vvp.commands += &&
verilognize_vvp.commands += vvp -M. -msimulinho_vpi simulinho.vvp
QMAKE_EXTRA_TARGETS += verilognize_vvp

verilognize.name = Verilognize
verilognize.depends  = compiler_objvpi_clean
verilognize.depends += compiler_modulevpi_clean
verilognize.depends += compiler_objvpi_make_all
verilognize.depends += compiler_modulevpi_make_all
verilognize.depends += verilognize_vvp
verilognize.commands = -echo V E R I L O G N I Z E
QMAKE_EXTRA_TARGETS += verilognize
