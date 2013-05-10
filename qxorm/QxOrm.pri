#############################################################################
##
## http://www.qxorm.com/
## http://sourceforge.net/projects/qxorm/
## Original file by Lionel Marty
##
## This file is part of the QxOrm library
##
## This software is provided 'as-is', without any express or implied
## warranty. In no event will the authors be held liable for any
## damages arising from the use of this software.
##
## GNU Lesser General Public License Usage
## This file must be used under the terms of the GNU Lesser
## General Public License version 2.1 as published by the Free Software
## Foundation and appearing in the file 'license.lgpl.txt' included in the
## packaging of this file.  Please review the following information to
## ensure the GNU Lesser General Public License version 2.1 requirements
## will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
##
## If you have questions regarding the use of this file, please contact :
## contact@qxorm.com
##
#############################################################################

############################
# Qt GUI module dependency #
############################

# To remove QtGui dependency :
#   1- in "./include/QxCommon/QxConfig.h" file, modify "_QX_ENABLE_QT_GUI_DEPENDENCY" constant to : "#define _QX_ENABLE_QT_GUI_DEPENDENCY 0"
#   2- in "./QxOrm.pri" file, add the following line : "QT -= gui"

 QT -= gui

###############################
# boost Library Configuration #
###############################

# In this section, it's necessary to specify boost directories (lib + include) and boost serialization module name (debug + release) :
#  - QX_BOOST_INCLUDE_PATH : your boost include path
#  - QX_BOOST_LIB_PATH : your boost lib path
#  - QX_BOOST_LIB_SERIALIZATION_DEBUG : your boost serialization module name in debug mode
#  - QX_BOOST_LIB_SERIALIZATION_RELEASE : your boost serialization module name in release mode

#QX_BOOST_INCLUDE_PATH = $$(BOOST_ROOT)                                      #$$quote(D:/Dvlp/_Libs/Boost/1_42/include)
#QX_BOOST_LIB_PATH     = $$(BOOST_ROOT)/stage/lib/                           #$$quote(D:/Dvlp/_Libs/Boost/1_42/lib_shared)
QX_BOOST_LIB_SERIALIZATION_DEBUG   = libboost_serialization #libboost_serialization-mgw46-mt-d-1_48   #"boost_serialization-vc90-mt-gd-1_42"
QX_BOOST_LIB_SERIALIZATION_RELEASE = libboost_serialization   #libboost_serialization-mgw46-mt-1_48#"boost_serialization-vc90-mt-1_42"

unix {
QX_BOOST_INCLUDE_PATH = $$quote(/usr/include)
QX_BOOST_LIB_PATH = $$quote(/usr/lib)
QX_BOOST_LIB_SERIALIZATION_DEBUG = "boost_serialization-mt-d"
QX_BOOST_LIB_SERIALIZATION_RELEASE = "boost_serialization-mt"
} # unix

##############################
# QxOrm Library Static Build #
##############################

# To create only 1 EXE including Qt, boost serialization and QxOrm libraries without any dependency :
#   1- be sure to build Qt and boost::serialization using static mode
#   2- in "./QxOrm.pri" file, add the following line : "DEFINES += _QX_STATIC_BUILD"
#   3- BUT PLEASE : in your program, add a "readme.txt" file and a "about my program..." window to indicate that your application is based on Qt, boost and QxOrm libraries !
# Note : on Windows, static mode works with only 1 EXE, it will never work mixing DLL and EXE (because of singleton implementation of boost::serialization and QxOrm libraries)

# DEFINES += _QX_STATIC_BUILD

######################
# Globals Parameters #
######################

CONFIG += debug_and_release
CONFIG += precompile_header
DEPENDPATH += .
INCLUDEPATH += ./qxorm
#INCLUDEPATH += $${QX_BOOST_INCLUDE_PATH}
QT += network
QT += xml
QT += sql
MOC_DIR = ./qt/moc
RCC_DIR = ./qt/rcc/src
UI_DIR = ./qt/ui
UI_HEADERS_DIR = ./qt/ui/include
UI_SOURCES_DIR = ./qt/ui/src

#############################
# Compiler / Linker Options #
#############################

win32 {
CONFIG(debug, debug|release) {
} else {
DEFINES += NDEBUG
win32-msvc2005: QMAKE_LFLAGS += /OPT:NOREF
win32-msvc2008: QMAKE_LFLAGS += /OPT:NOREF
win32-msvc2010: QMAKE_LFLAGS += /OPT:NOREF
} # CONFIG(debug, debug|release)
 win32-g++: QMAKE_LFLAGS += -Wl,-export-all-symbols
} # win32

#######################
# Externals Libraries #
#######################

#LIBS += -L$${QX_BOOST_LIB_PATH}

LIBS += -llibboost_serialization

