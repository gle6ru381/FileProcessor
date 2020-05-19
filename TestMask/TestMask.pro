QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    readmask_test.cpp \
    ../src/exception.cpp

HEADERS += \
    readmask_test.h
