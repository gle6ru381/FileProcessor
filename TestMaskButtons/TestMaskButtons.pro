QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_buttons.cpp \
    ../src/exception.cpp \
    ../src/mainwidget.cpp \
    ../src/mainwindow.cpp \
    ../src/mask.cpp \
    ../src/pushinsert.cpp \
    ../src/replace.cpp \
    ../src/styleSheet.cpp

HEADERS += \
    tst_buttons.h \
    ../src/exception.h \
    ../src/mainwidget.h \
    ../src/mainwindow.h \
    ../src/mask.h \
    ../src/pushinsert.h
