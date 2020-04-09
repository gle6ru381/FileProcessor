#include "../TestMask/readmask_test.h"
#include "mainwindow.h"

#include <QApplication>
#include <stdio.h>

int main(int argc, char* argv[])
{
    freopen("log.log", "w", stdout);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
