QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileProcessor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

HEADERS += \
    exception.h \
    mainwidget.h \
    mainwindow.h \
    mask.h \
    pushinsert.h

SOURCES += \
    exception.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp \
    mainwindowslots.cpp \
    mask.cpp \
    pushinsert.cpp \
    replace.cpp \
    styleSheet.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
