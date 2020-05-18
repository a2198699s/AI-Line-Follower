TEMPLATE = app
TARGET = enkisimulator
INCLUDEPATH += .

INCLUDEPATH += /usr/local/include/enki
INCLUDEPATH += /home/sama/Documents/CLDL/include

#INCLUDEPATH += add enki include path
#INCLUDEPATH += add clbp include path

# Input
HEADERS += Racer.h \
    bandpass.h \
    globals.h \
    parameters.h

SOURCES += run.cpp \
    Racer.cpp \
    bandpass.cpp

QT += opengl widgets
CONFIG          += qt warn_on debuge debug
QMAKE_CXXFLAGS += -std=c++0x -march=native -Wunused -pedantic -lenki
QMAKE_LFLAGS += -lenki

LIBS    += /home/sama/Documents/CLDL/libCLDL.a /home/sama/Documents/enkiSimulator/enki/libenki.a

#LIBS    += add libenki.a path here
#LIBS    += add libclBP.a path here

RESOURCES +=


#copydata.commands = $(COPY_DIR) $$PWD/cc.png $$OUT_PWD

#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata

