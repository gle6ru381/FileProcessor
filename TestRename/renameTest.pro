QT += testlib
QT += gui
QT += core
QT += widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

HEADERS += \
    ../src/exception.h \
    ../src/mainwidget.h \
    ../src/mainwindow.h \
    ../src/mask.h \
    ../src/pushinsert.h \
    rename_test.h

SOURCES +=  \
    rename_test.cpp \
    ../src/exception.cpp \
    ../src/mainwidget.cpp \
    ../src/mainwindow.cpp \
    ../src/mask.cpp \
    ../src/pushinsert.cpp \
    ../src/replace.cpp \
    ../src/styleSheet.cpp
