QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# Informa que as bibliotecas do RISCuinho quando for o caso serão
# :compartilhadas para uso externo
DEFINES += SIMULINHO_SHAREDLIB

# Usado pelo RTL e ferramentas de simulação
DEFINES += __SIMULINHO_DUMP__

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
    simulinho_vpi.h \
    simulinho_global_vpi.h


DISTFILES += \
    simulinho.v \
    ../SIMULinho-build-Desktop_RISCuinho-Profile/simulinho.vvp

unix:!macx: LIBS += -lvpi
unix:!macx: LIBS += -lveriuser

INCLUDEPATH += $$PWD/''
INCLUDEPATH += /usr/include/iverilog/

DEPENDPATH += $$PWD/''
DEPENDPATH += /usr/include/iverilog/

unix:!macx: PRE_TARGETDEPS += /usr/lib/i386-linux-gnu/libvpi.a
unix:!macx: PRE_TARGETDEPS += /usr/lib/i386-linux-gnu/libveriuser.a

## https://stackoverflow.com/questions/27683777/how-to-specify-compiler-flag-to-a-single-source-file-with-qmake
## http://doc.qt.io/qt-5/qmake-advanced-usage.html#adding-compilers
## configura riscuinho.cpp para ser compilado adequadamente para o vpi
SOURCES_OBJVPI = simulinho_vpi.cpp
objvpi.name = objvpi
objvpi.input = SOURCES_OBJVPI
objvpi.dependency_type = TYPE_C
#objvpi.depend_command = g++ -E -M ${QMAKE_FILE_NAME} | sed "s,^.*: ,,"
objvpi.variable_out = OBJECTS
objvpi.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
objvpi.commands = $${QMAKE_CXX} $(CXXFLAGS) \
                     -Wall -Wextra -Wshadow \
                     -fdebug-prefix-map=/build/iverilog-3pPO9t/iverilog-10.1=. \
                     -fstack-protector-strong -Wformat -Werror=format-security \
                     -fPIC $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}
QMAKE_EXTRA_COMPILERS += objvpi

SOURCES_VPI = simulinho_vpi.o
vpi.name = vpi
vpi.CONFIG += no_link
vpi.input = SOURCES_VPI
vpi.dependency_type = TYPE_C
vpi.depends = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
#vpi.depend_command = g++ -E -M ${QMAKE_FILE_NAME} | sed "s,^.*: ,,"
#vpi.variable_out = OBJECTS
vpi.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}.vpi
vpi.commands = $${QMAKE_CXX}  \
                --shared -lvpi -lveriuser $(INCPATH) \
                -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_IN} ## adiciona o -lvpi
QMAKE_EXTRA_COMPILERS += vpi

SOURCES_VERILOGNIZE = simulinho.v
verilognize_vvp.name = VerilognizeVVP
verilognize_vvp.CONFIG += no_link
verilognize_vvp.input = SOURCES_VERILOGNIZE
verilognize_vvp.depends = compiler_vpi_make_all
verilognize_vvp.variable_out= VERILOGNIZERS
verilognize_vvp.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}.vvp
verilognize_vvp.commands = iverilog -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_IN} ;\
                           vvp -M. -msimulinho_vpi ${QMAKE_FILE_OUT}
QMAKE_EXTRA_COMPILERS += verilognize_vvp
