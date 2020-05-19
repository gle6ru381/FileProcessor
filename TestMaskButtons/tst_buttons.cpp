#include "tst_buttons.h"
#include "../src/mainwindow.h"

buttons::buttons()
{
}

buttons::~buttons()
{
}

void buttons::test_case1()
{
    MainWindow* window = new MainWindow;
}

QTEST_MAIN(buttons)
