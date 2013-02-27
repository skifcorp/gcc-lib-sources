TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../src/sql2003.cpp \
    ../../src/mysql.cpp \
    ../../src/mysql/mysql_database.cpp

QMAKE_CXXFLAGS += -std=gnu++0x

LIBS           +=   -llibmysqlcppconn

DLLDESTDIR  = ../../lib
