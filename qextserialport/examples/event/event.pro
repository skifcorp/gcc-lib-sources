######################################################################
# Enumerator
######################################################################


PROJECT = event
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += ../../src
#INCLUDEPATH             += QtSources/4.8.1/include
QMAKE_LIBDIR += ../../src/build

OBJECTS_DIR    = tmp
MOC_DIR        = tmp
UI_DIR         = tmp

SOURCES += main.cpp PortListener.cpp
HEADERS += PortListener.h

#CONFIG(debug):LIBS  += -lqextserialportd
#else:LIBS  += -lqextserialport

LIBS  += -lqextserialport
