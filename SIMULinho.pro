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
    simulinho_vpi.h

INCLUDEPATH += \
    /usr/include/iverilog/

# apenas deve ser usado para segundo passo de compilação do vpi.
#LIBS += -lvpi

## https://stackoverflow.com/questions/27683777/how-to-specify-compiler-flag-to-a-single-source-file-with-qmake
## http://doc.qt.io/qt-5/qmake-advanced-usage.html#adding-compilers
## configura riscuinho.cpp para ser compilado adequadamente para o vpi
SOURCES_OBJVPI = simulinho_vpi.cpp
objvpi.name = objvpi
objvpi.input = SOURCES_OBJVPI
objvpi.dependency_type = TYPE_C
objvpi.variable_out = OBJECTS
objvpi.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
objvpi.commands = $${QMAKE_CXX} $(CXXFLAGS) -fpic $(INCPATH) -c ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT} ## adiciona o -fpic
QMAKE_EXTRA_COMPILERS += objvpi

SOURCES_VPI = simulinho_vpi.o
vpi.name = vpi
vpi.input = SOURCES_VPI
vpi.dependency_type = TYPE_C
vpi.depends = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
vpi.variable_out = OBJECTS
vpi.output = ${QMAKE_VAR_OBJECTS_DIR}${QMAKE_FILE_IN_BASE}.vpi
vpi.commands = $${QMAKE_CXX} $(CXXFLAGS) --shared -lvpi $(INCPATH) -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_IN} ## adiciona o -lvpi
QMAKE_EXTRA_COMPILERS += vpi
