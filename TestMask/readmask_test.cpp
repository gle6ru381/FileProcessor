#include "readmask_test.h"
#include "../src/mask.cpp"

ReadMask_Test::ReadMask_Test() : QObject()
{
}

ReadMask_Test::~ReadMask_Test()
{
}

void ReadMask_Test::test_case1()
{
    Mask a("file", "txt", "[N]");
    Mask b("file2", "txt", "[N5]");
    Mask c("text", "txt", "[N1]-[N]");

    QCOMPARE(a.getTotalName(), "file");
    QCOMPARE(b.getTotalName(), "2");
    QCOMPARE(c.getTotalName(), "t-text");
}

QTEST_APPLESS_MAIN(ReadMask_Test)
