#include "rename_test.h"
#include "../src/mainwindow.h"
// add necessary includes here

renameTest::renameTest()
{
}

renameTest::~renameTest()
{
}

void renameTest::test_rename_data()
{
    QTest::addColumn<QString>("find");
    QTest::addColumn<QString>("mask");
    QTest::addColumn<QString>("replace");
    QTest::addColumn<QString>("expect");

    QTest::newRow("data_1") << "abc"
                            << "[N]-[N]"
                            << "123"
                            << "[123]-[123]";
    QTest::newRow("data_2") << "76FA@#"
                            << "[N1-2]-[YMD]"
                            << "abc"
                            << "";
    QTest::newRow("data_3") << "my_name.ad"
                            << "[mhs]-[YMD]+[N]"
                            << "name";
    QTest::newRow("data_4") << ";;Tras"
                            << "[C1,5]and[C1,1]=[N]"
                            << "123";
}

void renameTest::test_rename()
{
    MainWindow* window = new MainWindow;
    MainWidget* main = window->getMainWidget();
    QFETCH(QString, find);
    QFETCH(QString, mask);
    QFETCH(QString, replace);
    beginName = find;
    for (int i = 0; i <= 10; i++) {
        QFile newFile(find + ".txt");
        newFile.open(QIODevice::WriteOnly | QIODevice::Text);
        newFile.close();
        QCOMPARE(newFile.exists(), true);
        main->addElement(new QFileInfo(find + ".txt"));
    }

    connect(window,
            SIGNAL(test_signal(QString const&)),
            this,
            SLOT(compare_name(QString const&)));

    QTest::keyClicks(window->findEdit(), find);
    QTest::keyClicks(window->maskEdit(), mask);
    QTest::keyClicks(window->replaceEdit(), replace);
    QTest::mouseClick(window->getFandr(), Qt::LeftButton);

    delete window;
}

void renameTest::compare_name(QString const& totalName)
{
    QString oldName(beginName + ".txt");
    QCOMPARE(beginName, totalName + ".txt");
}

QTEST_MAIN(renameTest)
