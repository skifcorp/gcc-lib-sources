#
TEMPLATE = subdirs
CONFIG   += ordered
SUBDIRS  = src \
           examples/enumerator \
           examples/event

QMAKE_CXXFLAGS += -std=c++0x# -m32
#QMAKE_LFLAGS   += -m32
