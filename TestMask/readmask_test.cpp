#include "readmask_test.h"
#include "../src/mask.cpp"

ReadMask_Test::ReadMask_Test() : QObject()
{
}

ReadMask_Test::~ReadMask_Test()
{
}

void ReadMask_Test::test_case1_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("mask");
    QTest::addColumn<QString>("result");

    QTest::newRow("1") << "file"
                       << "[N]"
                       << "file";
    QTest::newRow("2") << "text"
                       << "[N1]-[N]"
                       << "t-text";
    QTest::newRow("3") << "text"
                       << "[E1-3][N]"
                       << "/En1-3/text";
    QTest::newRow("4") << "abcd"
                       << "[N2-4][N3,2]-[E].[E1-3]"
                       << "bcdcd-/E/./En1-3/";
    QTest::newRow("testDate") << "abcd"
                              << "[Y-M-D]"
                              << "/Y/-/M/-/D/";
    QTest::newRow("testDate2") << "text"
                               << "[D:Y:M]"
                               << "/D/:/Y/:/M/";
    QTest::newRow("testDate3") << "bcd"
                               << "[N][M]-[E][Y-D]"
                               << "bcd/M/-/E//Y/-/D/";
    QTest::newRow("testDate4") << "file"
                               << "abc[Y,M,D]-[D;M;Y]"
                               << "abc/Y/,/M/,/D/-/D/;/M/;/Y/";
    QTest::newRow("testTime1") << "text"
                               << "[hms]-[h-m-s]"
                               << "/h//m//s/-/h/-/m/-/s/";
    QTest::newRow("testTime2") << "abs"
                               << "[N]-[h];[m;h;s]-[YMD]"
                               << "abs-/h/;/m/;/h/;/s/-/Y//M//D/";
    QTest::newRow("testTime3") << "nbd"
                               << "[ms;h]-[s;hm]"
                               << "/m//s/;/h/-/s/;/h//m/";
    QTest::newRow("testIter") << "text"
                              << "[C]"
                              << "/C0/";
    QTest::newRow("testIter2") << "text"
                               << "[C2,1][C]"
                               << "/C0//C1/";
    QTest::newRow("testIter3") << "text"
                               << "[C2,1]-[YMD][N];[C10]"
                               << "/C0/-/Y//M//D/text;/C1/";
}

void ReadMask_Test::test_case1()
{
    QFETCH(QString, name);
    QFETCH(QString, mask);
    QFETCH(QString, result);
    Mask a(name, mask);
    a.readName();
    QCOMPARE(a.getTotalName(), result);
}

void ReadMask_Test::test_step_and_value_data()
{
    QTest::addColumn<QString>("mask");
    QTest::addColumn<QVector<uint>>("resultValue");

    QTest::newRow("test1") << "[C1,2]" << QVector<uint>{1, 3, 5, 7};
    QTest::newRow("test2") << "[C5,5]" << QVector<uint>{5, 10, 15, 20};
    QTest::newRow("test3") << "[C]" << QVector<uint>{1, 2, 3, 4, 5};
}

void ReadMask_Test::test_step_and_value()
{
    QFETCH(QString, mask);
    QFETCH(QVector<uint>, resultValue);

    Mask a("text", mask);
    a.readName();
    for (int i = 0; i < resultValue.size(); i++) {
        QCOMPARE(a.getValue_C(0), resultValue[i]);
    }
}

QTEST_APPLESS_MAIN(ReadMask_Test)
