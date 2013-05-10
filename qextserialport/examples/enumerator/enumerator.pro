######################################################################
# Enumerator
######################################################################


PROJECT = enumerator
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH  += ../../src
#INCLUDEPATH             += QtSources/4.8.1/include
QMAKE_LIBDIR += ../../src/build

OBJECTS_DIR    = tmp
MOC_DIR        = tmp
UI_DIR         = tmp

SOURCES += main.cpp

CONFIG(debug, debug|release):LIBS  += -lqextserialportd
else:LIBS  += -lqextserialport
win32:LIBS += -lsetupapi
